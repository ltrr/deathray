#include "scene/scenedescription.h"

#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "background/sky.h"
#include "util/vector.h"
#include "scene/camera.h"
#include "scene/viewport.h"
#include "surface/sphere.h"
#include "surface/triangle.h"
#include "material/blinnphong.h"
#include "light/light.h"
#include "light/pointlight.h"
#include "light/sun.h"
#include "material/material.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "scene/scene.h"
#include "shader/shader.h"
#include "shader/normalshader.h"
#include "shader/depthshader.h"
#include "shader/blinnphongshader.h"
#include "util/objparser.h"
using std::string;
using std::shared_ptr;



//// user types ////
template<typename T>
struct UserType
{
    static constexpr const char* name = nullptr;
};


template<>
struct UserType<Camera>
{
    static constexpr const char* name = "camera";
};


template<>
struct UserType<Viewport>
{
    static constexpr const char* name = "viewport";
};


template<>
struct UserType<Surface>
{
    static constexpr const char* name = "surface";
};


template<>
struct UserType<Scene>
{
    static constexpr const char* name = "scene";
};


template<>
struct UserType<Material>
{
    static constexpr const char* name = "material";
};


template<>
struct UserType<Background>
{
    static constexpr const char* name = "background";
};


template<>
struct UserType<Shader>
{
    static constexpr const char* name = "shader";
};


template<>
struct UserType<Light>
{
    static constexpr const char* name = "light";
};


//// lua type templates ////
template<typename T>
struct LuaOp
{
    static T check(lua_State *L, int idx);
    static bool is(lua_State *L, int idx);
};


template<>
struct LuaOp<int>
{
    static int check(lua_State *L, int idx)
    {
        return luaL_checkinteger(L, idx);
    }

    static bool is(lua_State *L, int idx)
    {
        return lua_isinteger(L, idx);
    }
};


template<>
struct LuaOp<float>
{
    static float check(lua_State *L, int idx)
    {
        return luaL_checknumber(L, idx);
    }

    static bool is(lua_State *L, int idx)
    {
        return lua_isnumber(L, idx);
    }
};


template<>
struct LuaOp<string>
{
    static string check(lua_State *L, int idx)
    {
        return string(luaL_checkstring(L, idx));
    }

    static bool is(lua_State *L, int idx)
    {
        return lua_isstring(L, idx);
    }
};


template<>
struct LuaOp<Vec3>
{
    static Vec3 check(lua_State *L, int idx)
    {
        if (idx < 0)
            idx += lua_gettop(L) + 1; // correct for negative indices
        float x, y, z;               // ...
        lua_geti(L, idx, 1);         // ... x
        x = luaL_checknumber(L, -1); // ... x
        lua_geti(L, idx, 2);         // ... x y
        y = luaL_checknumber(L, -1); // ... x y
        lua_geti(L, idx, 3);         // ... x y z
        z = luaL_checknumber(L, -1); // ... x y z
        lua_pop(L, 3);               // ...
        return Vec3(x, y, z);
    }

    static bool is(lua_State *L, int idx)
    {
        if (idx < 0)
            idx += lua_gettop(L) + 1; // correct for negative indices
        if (!lua_istable(L, idx)) return false;
        lua_geti(L, idx, 1);         // ... x
        lua_geti(L, idx, 2);         // ... x y
        lua_geti(L, idx, 3);         // ... x y z
        bool ok = (LuaOp<float>::is(L, -1)
                   && LuaOp<float>::is(L, -2)
                   && LuaOp<float>::is(L, -3));
        lua_pop(L, 3);               // ...
        return ok;
    }
};


template<typename T>
struct LuaOp<shared_ptr<T>>
{
    static_assert(UserType<T>::name != nullptr,
                 "shared_ptr operations requires named type");

    static shared_ptr<T> check(lua_State *L, int idx)
    {
        return *((shared_ptr<T> *) luaL_checkudata(L, idx, UserType<T>::name));
    }

    static bool is(lua_State *L, int idx)
    {
        void *p = luaL_testudata(L, idx, UserType<T>::name);
        return p != nullptr;
    }

    static void registerudata(lua_State *L)
    {
        luaL_newmetatable(L, UserType<T>::name); // meta
        lua_pushstring(L, "__gc");               // meta '__gc'
        lua_pushcfunction(L, gc);                // meta '__gc' gc
        lua_settable(L, -3);                     // meta
        lua_pop(L, 1);                           //
    }

    static int gc(lua_State *L)
    {
        auto p = (shared_ptr<T> *) luaL_checkudata(L, 1, UserType<T>::name);
        p->reset();
        return 0;
    }

    static shared_ptr<T> newuserdata(lua_State *L, T *p)
    {
        void *addr = lua_newuserdata(L, sizeof(shared_ptr<T>));
        auto *addr_ = new (addr) shared_ptr<T>(p);
        luaL_setmetatable(L, UserType<T>::name);
        return *addr_;
    }

    static shared_ptr<T> pushuserdata(lua_State *L, shared_ptr<T> p)
    {
        void *addr = lua_newuserdata(L, sizeof(shared_ptr<T>));
        auto *addr_ = new (addr) shared_ptr<T>(p);
        luaL_setmetatable(L, UserType<T>::name);
        return *addr_;
    }
};


template <typename T>
bool getintable(lua_State *L, int table_idx, const char* idx, T& result)
{
    lua_pushstring(L, idx);                  // ... idx
    lua_gettable(L, table_idx);               // ... obj
    if (!LuaOp<T>::is(L, -1)) {
        lua_pop(L, 1);                         // ...
        return false;
    }
    result = LuaOp<T>::check(L, -1);          // ... obj
    lua_pop(L, 1);                            // ...
    return true;
}


template <typename T>
bool getintable(lua_State *L, int table_idx, int idx, T& result)
{
    lua_geti(L, table_idx, idx);               // ... obj
    if (!LuaOp<T>::is(L, -1)) {
        lua_pop(L, 1);                         // ...
        return false;
    }
    result = LuaOp<T>::check(L, -1);          // ... obj
    lua_pop(L, 1);                            // ...
    return true;
}


template <typename T>
bool getintable(lua_State *L, int table_idx, const char* idx, T& result,
                const T& default_)
{
    if (!getintable(L, table_idx, idx, result)) {
        result = default_;
        return false;
    }
    return true;
}


template <typename T>
bool getintable(lua_State *L, int table_idx, int idx, T& result,
                const T& default_)
{
    if (!getintable(L, table_idx, idx, result)) {
        result = default_;
        return false;
    }
    return true;
}


template <typename T>
int unsafe_getsetting(lua_State *L)
{   // *result *name
    T *p = (T *) lua_touserdata(L, 1);
    const char *name = (const char *) lua_touserdata(L, 2);
    lua_getglobal(L, name);
    *p = LuaOp<T>::check(L, 3);
    return 0;
}


//// lua CFunctions ////
static int scene_lookat(lua_State* L)
{
    Vec3 origin, target, up;
    float aspect, fov;
    getintable(L, 1, "origin", origin);
    getintable(L, 1, "target", target);
    getintable(L, 1, "up", up);
    getintable(L, 1, "aspect", aspect);
    getintable(L, 1, "fov", fov);

    LuaOp<CameraPtr>::newuserdata(L, new PerspectiveCamera(origin, target, up, fov, aspect));
    return 1;
}


static int scene_mkviewport(lua_State* L)  // { width=, height= }
{
    int width, height;
    getintable(L, 1, "width", width);
    getintable(L, 1, "height", height);

    LuaOp<ViewportPtr>::newuserdata(L, new Viewport(width, height));
    return 1;
}


static int scene_mklambert(lua_State* L)   // albedo
{
    Vec3 albedo = LuaOp<Vec3>::check(L, 1); // albedo
    lua_pop(L, 1);                          //

    LuaOp<MaterialPtr>::newuserdata(L, new Lambertian(albedo));
    return 1;
}


static int scene_mkmetal(lua_State* L)   // { albedo=, fuzz= }
{
    Vec3 albedo;
    float fuzz;
    getintable(L, 1, "albedo", albedo);
    getintable(L, 1, "fuzz", fuzz, 0.0f);

    LuaOp<MaterialPtr>::newuserdata(L, new Metal(albedo, fuzz));
    return 1;
}


static int scene_mkblinnphong(lua_State* L)   // { albedo=, fuzz= }
{
    Vec3 specular, diffuse, ambient;
    float shiness;
    getintable(L, 1, "specular", specular, Vec3(0,0,0));
    getintable(L, 1, "diffuse", diffuse, Vec3(0,0,0));
    getintable(L, 1, "ambient", ambient, Vec3(0,0,0));
    getintable(L, 1, "shiness", shiness, 0.0f);

    LuaOp<MaterialPtr>::newuserdata(L,
        new BlinnPhong(diffuse, specular, ambient, shiness));
    return 1;
}


static int scene_mksphere(lua_State* L)   // { center, radius }
{
    Vec3 center;
    float radius;
    MaterialPtr mat;
    getintable(L, 1, "center", center);
    getintable(L, 1, "radius", radius);
    getintable(L, 1, "material", mat);

    LuaOp<SurfacePtr>::newuserdata(L, new Sphere(center, radius, mat));
    return 1;
}


static int scene_mktriangle(lua_State* L)   // { p1, p2, p3, material= }
{
    Vec3 p1, p2, p3;
    MaterialPtr mat;
    getintable(L, 1, 1, p1);
    getintable(L, 1, 2, p2);
    getintable(L, 1, 3, p3);
    getintable(L, 1, "material", mat);

    LuaOp<SurfacePtr>::newuserdata(L, new Triangle(p1, p2, p3, mat));
    return 1;
}


static int scene_loadobj(lua_State* L)   // filename
{
    string filename(LuaOp<string>::check(L, 1));
    auto result = parseObj(filename);
    lua_settop(L, 0);                   //

    if (!result.ok) {
        luaL_error(L, "error reading mesh from file %s", filename.c_str());
    }

    lua_createtable(L, result.surfaces.size(), 0);               // table
    for (int i = 0; i < result.surfaces.size(); i++) {
        LuaOp<SurfacePtr>::pushuserdata(L, result.surfaces[i]);  // table surf
        lua_seti(L, 1, i+1);                                     // table
    }
    return 1;
}


static int scene_mkpointlight(lua_State* L)
{
    Vec3 position, intensity;
    getintable(L, 1, "position", position);
    getintable(L, 1, "intensity", intensity);

    LuaOp<LightPtr>::newuserdata(L, new PointLight(position, intensity));
    return 1;
}


static int scene_mksun(lua_State* L)
{
    Vec3 direction, intensity;
    getintable(L, 1, "direction", direction);
    getintable(L, 1, "intensity", intensity);

    LuaOp<LightPtr>::newuserdata(L, new Sun(direction, intensity));
    return 1;
}


static int scene_mksky(lua_State* L)   // { zenith, nadir }
{
    Vec3 zenith, nadir;
    getintable(L, 1, "zenith", zenith);
    getintable(L, 1, "nadir", nadir);

    LuaOp<BackgroundPtr>::newuserdata(L, new Sky(zenith, nadir));
    return 1;
}


static int scene_mkdepthrender(lua_State* L)   // { foreground=, background=, maxdepth= }
{
    Vec3 fg, bg;
    float maxdepth;
    getintable(L, 1, "foreground", fg, Vec3(1,1,1));
    getintable(L, 1, "background", bg, Vec3(0,0,0));
    getintable(L, 1, "maxdepth", maxdepth, 1.0f);

    LuaOp<ShaderPtr>::newuserdata(L, new DepthShader(maxdepth, fg, bg));
    return 1;
}


static int scene_mknormalrender(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new NormalShader());
    return 1;
}


static int scene_mkblinnphongshader(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new BlinnPhongShader());
    return 1;
}


static void add_surfaces(lua_State* L, Scene* scene) // ... (table|obj)
{
    if (lua_istable(L, -1)) {                        // ... table
        lua_len(L, -1);                               // ... table len
        int len = lua_tointeger(L, -1);              // ... table len
        lua_pop(L, 1);                               // ... table
        for (int i = 1; i <= len; i++) {
            lua_geti(L, -1, i);                      // ... table (table|obj)
            add_surfaces(L, scene);                  // ... table (table|obj)
            lua_pop(L, 1);                           // ... table
        }
    }
    else if (LuaOp<SurfacePtr>::is(L, -1)) {
        SurfacePtr surface = LuaOp<SurfacePtr>::check(L, -1);  // table surf
        scene->addSurface(surface);                            // table surf
    }
    else if(LuaOp<LightPtr>::is(L, -1)) {
        LightPtr light = LuaOp<LightPtr>::check(L, -1);        // table light
        scene->addLight(light);                                // table light
    }
}


static int scene_mkscene(lua_State* L) // { obj1, obj2, {objs}, ..., bg = }
{
    BackgroundPtr bg;
    Color3f ambient;
    getintable(L, 1, "bg", bg);
    getintable(L, 1, "ambient", ambient, Vec3(0,0,0));
    /*
    lua_pushliteral(L, "bg");                  // {objs} 'bg'
    lua_gettable(L, 1);                        // {objs} bg
    auto bg = LuaOp<BackgroundPtr>::check(L, -1);    // {objs} bg
    lua_pop(L, 1);                             // {objs}*/
    Scene *newscene = new Scene(bg);
    newscene->ambient() = ambient;
    add_surfaces(L, newscene);                 // {objs}
    lua_settop(L, 0);                          //
    LuaOp<ScenePtr>::newuserdata(L, newscene); // scene
    return 1;
}


luaL_Reg scene_lib[] = {
    { "lookat", scene_lookat },
    { "mkviewport", scene_mkviewport },
    { "sphere", scene_mksphere },
    { "triangle", scene_mktriangle },
    { "loadobj", scene_loadobj },
    { "lambert", scene_mklambert },
    { "metal", scene_mkmetal },
    { "blinn_phong", scene_mkblinnphong },
    { "sky", scene_mksky },
    { "pointlight", scene_mkpointlight },
    { "sun", scene_mksun },
    { "depthshader", scene_mkdepthrender },
    { "normalshader", scene_mknormalrender },
    { "blinn_phong_shader", scene_mkblinnphongshader },
    { "mkscene", scene_mkscene },
    { nullptr, nullptr }
};


static int luaopen_scene(lua_State* L)
{
    LuaOp<ScenePtr>::registerudata(L);
    LuaOp<CameraPtr>::registerudata(L);
    LuaOp<ViewportPtr>::registerudata(L);
    LuaOp<SurfacePtr>::registerudata(L);
    LuaOp<MaterialPtr>::registerudata(L);
    LuaOp<BackgroundPtr>::registerudata(L);
    LuaOp<ShaderPtr>::registerudata(L);
    LuaOp<LightPtr>::registerudata(L);

    lua_getglobal(L, "_G");           // _G
    luaL_setfuncs(L, scene_lib, 0);   // _G
    lua_pop(L, 1);                    //
    return 0;
}


//// class SceneDescription ////
SceneDescription::SceneDescription(lua_State *L)
{
    this->L = L;
}


SceneDescription::~SceneDescription()
{
    lua_close(L);
}


SceneDescription SceneDescription::fromFile(const string& filename)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_scene(L);
    bool error = luaL_dofile(L, filename.c_str());
    if (error) {
        const char* msg = lua_tostring(L, -1);
        std::cerr << "error loading file " << filename << '\n'
                  << msg << std::endl;
        exit(1);
    }
    return SceneDescription(L);
}


template <typename T>
T SceneDescription::getSetting(const string& name, const T& default_) const
{
    T val;
    lua_getglobal(L, "_G");           // _G
    lua_pushstring(L, name.c_str());  // _G name
    lua_gettable(L, 1);               // _G val

    if (lua_isnil(L, 2)) { // not set
        lua_pop(L, 2);                //
        return default_;
    }
    else {
        const char* name_c = name.c_str();
        lua_pushcfunction(L, unsafe_getsetting<T>);
        lua_pushlightuserdata(L, &val);
        lua_pushlightuserdata(L, (void*) name_c);
        int status = lua_pcall(L, 2, 0, 0);
        if (status == LUA_OK) {
            lua_settop(L, 0);
            return val;
        }
        else {
            const char *error = lua_tostring(L, -1);
            std::cerr << "error obtaining setting '" << name << "':" << '\n'
                      << error << '\n'
                      << "exiting." << std::endl;
            exit(1);
        }
    }
}


template <typename T>
T SceneDescription::getSetting(const string& name) const
{
    lua_getglobal(L, "_G");           // _G
    lua_pushstring(L, name.c_str());  // _G name
    lua_gettable(L, 1);               // _G val

    T val;
    const char* name_c = name.c_str();
    lua_pushcfunction(L, unsafe_getsetting<T>);
    lua_pushlightuserdata(L, &val);
    lua_pushlightuserdata(L, (void*) name_c);
    int status = lua_pcall(L, 2, 0, 0);
    if (status == LUA_OK) {
        lua_settop(L, 0);
        return val;
    }
    else {
        const char *error = lua_tostring(L, -1);
        std::cerr << "error obtaining setting '" << name << "':" << '\n'
                  << error << '\n'
                  << "exiting." << std::endl;
        exit(1);
    }
}



//// Explicit instatiations ////
template
string SceneDescription::getSetting(const string& name) const;


template
string SceneDescription::getSetting(const string& name, const string& default_) const;


template
float SceneDescription::getSetting(const string& name) const;


template
float SceneDescription::getSetting(const string& name, const float& default_) const;


template
int SceneDescription::getSetting(const string& name) const;


template
int SceneDescription::getSetting(const string& name, const int& default_) const;


template
Vec3 SceneDescription::getSetting(const string& name) const;


template
Vec3 SceneDescription::getSetting(const string& name, const Vec3& default_) const;


template
shared_ptr<Camera> SceneDescription::getSetting(const string& name) const;


template
shared_ptr<Viewport> SceneDescription::getSetting(const string& name) const;


template
shared_ptr<Surface> SceneDescription::getSetting(const string& name) const;


template
shared_ptr<Scene> SceneDescription::getSetting(const string& name) const;


template
ShaderPtr SceneDescription::getSetting(const string& name) const;

template
ShaderPtr SceneDescription::getSetting(const string& name, const ShaderPtr& default_) const;
