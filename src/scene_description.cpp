#include "scene_description.h"

#include <string>
#include <memory>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "vector.h"
#include "camera.h"
#include "viewport.h"
using std::string;
using std::shared_ptr;



//// lua type templates ////
template<typename T>
static T check(lua_State *L, int idx);


template<>
string check(lua_State* L, int idx)
{
    return string(luaL_checkstring(L, idx));
}


template<>
int check(lua_State* L, int idx)
{
    return luaL_checkinteger(L, idx);
}


template<>
float check(lua_State *L, int idx)
{
    return luaL_checknumber(L, idx);
}


template<>
Vec3 check(lua_State *L, int idx)
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


template<>
shared_ptr<Camera> check(lua_State *L, int idx)
{
    return *((shared_ptr<Camera> *) luaL_checkudata(L, idx, "camera"));
}


template<>
shared_ptr<Viewport> check(lua_State *L, int idx)
{
    return *((shared_ptr<Viewport> *) luaL_checkudata(L, idx, "viewport"));
}



template <typename T>
int unsafe_getsetting(lua_State *L)
{   // *result *name
    T *p = (T *) lua_touserdata(L, 1);
    const char *name = (const char *) lua_touserdata(L, 2);
    lua_getglobal(L, name);
    *p = check<T>(L, 3);
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
static int scene_lookat(lua_State* L)      // table
{
    lua_pushliteral(L, "origin");          // table 'origin'
    lua_gettable(L, 1);                    // table origin
    Vec3 origin = check<Vec3>(L, -1);      // table origin
    lua_pop(L, 1);                         // table

    lua_pushliteral(L, "target");          // table 'target'
    lua_gettable(L, 1);                    // table target
    Vec3 target = check<Vec3>(L, -1);      // table target
    lua_pop(L, 1);                         // table

    lua_pushliteral(L, "up");              // table 'up'
    lua_gettable(L, 1);                    // table up
    Vec3 up = check<Vec3>(L, -1);          // table up
    lua_pop(L, 1);                         // table

    lua_pushliteral(L, "aspect");           // table 'aspect'
    lua_gettable(L, 1);                     // table aspect
    float aspect = luaL_checknumber(L, -1); // table aspect
    lua_pop(L, 1);                          // table

    lua_pushliteral(L, "fov");             // table 'fov'
    lua_gettable(L, 1);                    // table fov
    float fov = luaL_checknumber(L, -1);   // table fov
    lua_pop(L, 2);                         //

    PerspectiveCamera temp = PerspectiveCamera::lookat(origin, target, up, fov, aspect);
    shared_ptr<Camera> *cam =
        (shared_ptr<Camera> *) lua_newuserdata(L, sizeof(shared_ptr<Camera>));
    *cam = shared_ptr<Camera>(new PerspectiveCamera(temp));
    luaL_setmetatable(L, "camera");
    return 1;
}


static int scene_mkviewport(lua_State* L)  // width, height
{
    lua_pushliteral(L, "width");          // table 'width'
    lua_gettable(L, 1);                    // table width
    int width = check<int>(L, -1);         // table width
    lua_pop(L, 1);                         // table

    lua_pushliteral(L, "height");          // table 'height'
    lua_gettable(L, 1);                    // table height
    int height = check<int>(L, -1);        // table height
    lua_pop(L, 1);                         // table

    shared_ptr<Viewport> vp(new Viewport(width, height));
    shared_ptr<Viewport> *vpp =
        (shared_ptr<Viewport> *) lua_newuserdata(L, sizeof(shared_ptr<Viewport>));
    *vpp = vp;
    luaL_setmetatable(L, "viewport");
    return 1;
}


luaL_Reg scene_lib[] = {
    { "lookat", scene_lookat },
    { "mkviewport", scene_mkviewport },
    { nullptr, nullptr }
};


static int luaopen_scene(lua_State* L)
{
    luaL_newmetatable(L, "camera");
    luaL_newmetatable(L, "viewport");
    /*
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, scene_cameraviewport_gc);
    lua_settable(L, -3);
    */

    lua_getglobal(L, "_G");
    luaL_setfuncs(L, scene_lib, 0);

    lua_settop(L, 0);
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
    luaL_dofile(L, filename.c_str());
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
