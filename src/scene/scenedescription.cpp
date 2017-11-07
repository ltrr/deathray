/*
#include "scene/scenedescription.h"


#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "lua/op.h"
#include "lua/scene.h"

using std::string;
using std::shared_ptr;



template <typename T>
int unsafe_getsetting(lua_State *L)
{   // *result *name
    T *p = (T *) lua_touserdata(L, 1);
    const char *name = (const char *) lua_touserdata(L, 2);
    lua_getglobal(L, name);
    *p = LuaOp<T>::check(L, 3);
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
shared_ptr<Scene> SceneDescription::getSetting(const string& name) const;


template
ShaderPtr SceneDescription::getSetting(const string& name) const;

template
ShaderPtr SceneDescription::getSetting(const string& name, const ShaderPtr& default_) const;
*/
