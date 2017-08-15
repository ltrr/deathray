#include "scene_description.h"

#include <string>
#include <memory>
#include <new>
#include <type_traits>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "vector.h"
#include "camera.h"
#include "viewport.h"
#include "sphere.h"
#include "triangle.h"
#include "scene.h"
#include "material.h"
#include "lambert.h"
#include "metal.h"
#include "sky.h"
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
struct UserType<Object>
{
    static constexpr const char* name = "object";
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


//// lua type templates ////
template<typename T>
struct LuaOp
{
    static T check(lua_State *L, int idx);
};


template<>
struct LuaOp<int>
{
    static int check(lua_State *L, int idx)
    {
        return luaL_checkinteger(L, idx);
    }
};


template<>
struct LuaOp<float>
{
    static float check(lua_State *L, int idx)
    {
        return luaL_checknumber(L, idx);
    }
};


template<>
struct LuaOp<string>
{
    static string check(lua_State *L, int idx)
    {
        return string(luaL_checkstring(L, idx));
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
};


template <typename T>
int unsafe_getsetting(lua_State *L)
{   // *result *name
    T *p = (T *) lua_touserdata(L, 1);
    const char *name = (const char *) lua_touserdata(L, 2);
    lua_getglobal(L, name);
    *p = LuaOp<T>::check(L, 3);
    return 0;
}


template <typename T>
static T _getsetting(lua_State *L, const string& name)
{
    T val;
    const char* name_c = name.data();
    lua_pushcfunction(L, unsafe_getsetting<T>);
    lua_pushlightuserdata(L, &val);
    lua_pushlightuserdata(L, (void*) name_c);
    int status = lua_pcall(L, 2, 0, 0);
    if (status == LUA_OK) {
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


template <typename T>
static T _getsetting(lua_State *L, const std::string& name, const T& default_)
{
    T val;
    const char* name_c = name.c_str();
    lua_pushcfunction(L, unsafe_getsetting<T>);
    lua_pushlightuserdata(L, &val);
    lua_pushlightuserdata(L, (void*) name_c);
    int status = lua_pcall(L, 2, 0, 0);
    if (status == LUA_OK) {
        return val;
    }
    else {
        return default_;
    }
}



//// lua CFunctions ////
static int scene_lookat(lua_State* L)         // table
{
    lua_pushliteral(L, "origin");             // table 'origin'
    lua_gettable(L, 1);                       // table origin
    Vec3 origin = LuaOp<Vec3>::check(L, -1);  // table origin
    lua_pop(L, 1);                            // table

    lua_pushliteral(L, "target");             // table 'target'
    lua_gettable(L, 1);                       // table target
    Vec3 target = LuaOp<Vec3>::check(L, -1);  // table target
    lua_pop(L, 1);                            // table

    lua_pushliteral(L, "up");                 // table 'up'
    lua_gettable(L, 1);                       // table up
    Vec3 up = LuaOp<Vec3>::check(L, -1);      // table up
    lua_pop(L, 1);                            // table

    lua_pushliteral(L, "aspect");             // table 'aspect'
    lua_gettable(L, 1);                       // table aspect
    float aspect = luaL_checknumber(L, -1);   // table aspect
    lua_pop(L, 1);                            // table

    lua_pushliteral(L, "fov");                // table 'fov'
    lua_gettable(L, 1);                       // table fov
    float fov = luaL_checknumber(L, -1);      // table fov
    lua_pop(L, 2);                            //

    PerspectiveCamera temp = PerspectiveCamera::lookat(origin, target, up, fov, aspect);
    LuaOp<shared_ptr<Camera>>::newuserdata(L, new PerspectiveCamera(temp));
    return 1;
}


static int scene_mkviewport(lua_State* L)  // width, height
{
    lua_pushliteral(L, "width");           // table 'width'
    lua_gettable(L, 1);                    // table width
    int width = LuaOp<int>::check(L, -1);  // table width
    lua_pop(L, 1);                         // table

    lua_pushliteral(L, "height");          // table 'height'
    lua_gettable(L, 1);                    // table height
    int height = LuaOp<int>::check(L, -1); // table height
    lua_pop(L, 1);                         // table

    LuaOp<shared_ptr<Viewport>>::newuserdata(L, new Viewport(width, height));
    return 1;
}


static int scene_mklambert(lua_State* L)   // albedo
{
    Vec3 albedo = LuaOp<Vec3>::check(L, 1); // albedo
    lua_pop(L, 1);                          //

    LuaOp<MaterialPtr>::newuserdata(L, new Lambert(albedo));
    return 1;
}


static int scene_mkmetal(lua_State* L)   // { albedo fuzz }
{
    lua_pushliteral(L, "albedo");            // table 'albedo'
    lua_gettable(L, 1);                      // table albedo
    Vec3 albedo = LuaOp<Vec3>::check(L, -1); // table albedo
    lua_pop(L, 1);                           // table

    lua_pushliteral(L, "fuzz");              // table 'fuzz'
    lua_gettable(L, 1);                      // table fuzz
    float fuzz = LuaOp<float>::check(L, -1); // table fuzz
    lua_pop(L, 1);                           // table

    LuaOp<MaterialPtr>::newuserdata(L, new Metal(albedo, fuzz));
    return 1;
}


static int scene_mksphere(lua_State* L)   // { center, radius }
{
    lua_pushliteral(L, "center");            // table 'center'
    lua_gettable(L, 1);                      // table center
    Vec3 center = LuaOp<Vec3>::check(L, -1); // table center
    lua_pop(L, 1);                           // table

    lua_pushliteral(L, "radius");              // table 'radius'
    lua_gettable(L, 1);                        // table radius
    float radius = LuaOp<float>::check(L, -1); // table radius
    lua_pop(L, 1);                             // table

    lua_pushliteral(L, "material");            // table 'material'
    lua_gettable(L, 1);                        // table material
    MaterialPtr mat = LuaOp<MaterialPtr>::check(L, -1); // table material
    lua_pop(L, 1);                             // table

    LuaOp<ObjectPtr>::newuserdata(L, new Sphere(center, radius, mat));
    return 1;
}


static int scene_mktriangle(lua_State* L)   // { p1, p2, p3, material= }
{
    lua_geti(L, 1, 1);                   // table p1
    Vec3 p1 = LuaOp<Vec3>::check(L, -1); // table p1
    lua_pop(L, 1);                       // table

    lua_geti(L, 1, 2);                   // table p2
    Vec3 p2 = LuaOp<Vec3>::check(L, -1); // table p2
    lua_pop(L, 1);                       // table

    lua_geti(L, 1, 3);                   // table p3
    Vec3 p3 = LuaOp<Vec3>::check(L, -1); // table p3
    lua_pop(L, 1);                       // table

    lua_pushliteral(L, "material");            // table 'material'
    lua_gettable(L, 1);                        // table material
    MaterialPtr mat = LuaOp<MaterialPtr>::check(L, -1); // table material
    lua_pop(L, 1);                             // table

    LuaOp<ObjectPtr>::newuserdata(L, new Triangle(p1, p2, p3, mat));
    return 1;
}


static int scene_mksky(lua_State* L)   // { zenith, nadir }
{
    lua_pushliteral(L, "zenith");            // table 'zenith'
    lua_gettable(L, 1);                      // table zenith
    Vec3 zenith = LuaOp<Vec3>::check(L, -1); // table zenith
    lua_pop(L, 1);                           // table

    lua_pushliteral(L, "nadir");            // table 'nadir'
    lua_gettable(L, 1);                      // table nadir
    Vec3 nadir = LuaOp<Vec3>::check(L, -1); // table nadir
    lua_pop(L, 1);

    LuaOp<BackgroundPtr>::newuserdata(L, new Sky(zenith, nadir));
    return 1;
}


static int scene_mkscene(lua_State* L)      // { obj1, obj2, ..., bg = }
{
    lua_pushliteral(L, "bg");               // {objs} 'bg'
    lua_gettable(L, 1);                     // {objs} bg
    auto bg = LuaOp<BackgroundPtr>::check(L, -1);    // {objs} bg
    lua_pop(L, 1);                          // {objs}

    lua_len(L, 1);                                      // {objs} len
    int len = lua_tointeger(L, -1);                     // {objs} len
    lua_pop(L, 1);                                      // {objs}
    Scene *newscene = new Scene(bg);
    for (int i = 1; i <= len; i++) {
        lua_geti(L, -1, i);                              // {objs}
        ObjectPtr obj = LuaOp<ObjectPtr>::check(L, -1);  // {objs} obj
        newscene->addobject(obj);
        lua_pop(L, 1);                                   // {objs}
    }
    lua_pop(L, 1);                                       //
    LuaOp<ScenePtr>::newuserdata(L, newscene);           // scene
    return 1;
}


luaL_Reg scene_lib[] = {
    { "lookat", scene_lookat },
    { "mkviewport", scene_mkviewport },
    { "sphere", scene_mksphere },
    { "triangle", scene_mktriangle },
    { "lambert", scene_mklambert },
    { "metal", scene_mkmetal },
    { "sky", scene_mksky },
    { "mkscene", scene_mkscene },
    { nullptr, nullptr }
};


static int luaopen_scene(lua_State* L)
{
    luaL_newmetatable(L, "camera"); // metacam
    lua_pushstring(L, "__gc");      // metacam '__gc'
    lua_pushcfunction(L, LuaOp<shared_ptr<Camera>>::gc); // metacam '__gc' gc
    lua_settable(L, -3);            // metacam
    lua_pop(L, 1);                  //

    luaL_newmetatable(L, "viewport"); // metavp
    lua_pushstring(L, "__gc");        // metavp '__gc'
    lua_pushcfunction(L, LuaOp<shared_ptr<Viewport>>::gc); // metavp '__gc' gc
    lua_settable(L, -3);              // metavp
    lua_pop(L, 1);                    //

    luaL_newmetatable(L, "object"); // metavp
    lua_pushstring(L, "__gc");        // metavp '__gc'
    lua_pushcfunction(L, LuaOp<shared_ptr<Object>>::gc); // metavp '__gc' gc
    lua_settable(L, -3);              // metavp
    lua_pop(L, 1);                    //

    luaL_newmetatable(L, "scene"); // metavp
    lua_pushstring(L, "__gc");        // metavp '__gc'
    lua_pushcfunction(L, LuaOp<shared_ptr<Scene>>::gc); // metavp '__gc' gc
    lua_settable(L, -3);              // metavp
    lua_pop(L, 1);                    //

    luaL_newmetatable(L, "material"); // metamat
    lua_pushstring(L, "__gc");        // metamat '__gc'
    lua_pushcfunction(L, LuaOp<shared_ptr<Material>>::gc); // metamat '__gc' gc
    lua_settable(L, -3);              // metamat
    lua_pop(L, 1);                    //

    luaL_newmetatable(L, "background"); // metabg
    lua_pushstring(L, "__gc");        // metabg '__gc'
    lua_pushcfunction(L, LuaOp<shared_ptr<Background>>::gc); // metabg '__gc' gc
    lua_settable(L, -3);              // metabg
    lua_pop(L, 1);                    //

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


SceneDescription SceneDescription::fromfile(const string& filename)
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
T SceneDescription::getsetting(const string& name, const T& default_) const
{
    return _getsetting<T>(L, name, default_);
}


template <typename T>
T SceneDescription::getsetting(const string& name) const
{
    return _getsetting<T>(L, name);
}



//// Explicit instatiations ////
template
string SceneDescription::getsetting(const string& name) const;


template
string SceneDescription::getsetting(const string& name, const string& default_) const;


template
float SceneDescription::getsetting(const string& name) const;


template
float SceneDescription::getsetting(const string& name, const float& default_) const;


template
int SceneDescription::getsetting(const string& name) const;


template
int SceneDescription::getsetting(const string& name, const int& default_) const;


template
Vec3 SceneDescription::getsetting(const string& name) const;


template
Vec3 SceneDescription::getsetting(const string& name, const Vec3& default_) const;


template
shared_ptr<Camera> SceneDescription::getsetting(const string& name) const;


template
shared_ptr<Viewport> SceneDescription::getsetting(const string& name) const;


template
shared_ptr<Object> SceneDescription::getsetting(const string& name) const;


template
shared_ptr<Scene> SceneDescription::getsetting(const string& name) const;
