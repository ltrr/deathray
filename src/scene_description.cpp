#include "scene_description.h"

#include <string>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "vector.h"
using std::string;

//// class SceneDescription
SceneDescription::SceneDescription(lua_State *L) {
    this->L = L;
}

SceneDescription::~SceneDescription() {
    lua_close(L);
}

SceneDescription SceneDescription::fromfile(const string& filename) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, filename.c_str());
    return SceneDescription(L);
}

template<typename T>
static bool check(lua_State *L, int index, T& val);

template<>
bool check(lua_State *L, int idx, string& val) {
    if (lua_isnil(L, idx))
        return false;
    if (!lua_isstring(L, idx))
        return false;
    val = string(lua_tostring(L, idx));
    return true;
}

template<>
bool check(lua_State *L, int idx, float& val) {
    if (lua_isnil(L, idx))
        return false;
    if (!lua_isnumber(L, idx))
        return false;
    val = float(lua_tonumber(L, idx));
    return true;
}

template<>
bool check(lua_State *L, int idx, Vec3& val) {
    if (lua_isnil(L, idx))
        return false;
    if (!lua_istable(L, idx))
        return false;
    float x, y, z;
    lua_geti(L, idx, 1); // x
    lua_geti(L, idx, 2); // x y
    lua_geti(L, idx, 3); // x y z
    if (check(L, 2, x) && check(L, 3, y) && check(L, 4, z)) {
        lua_settop(L, -4);
        val = Vec3(x, y, z);
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
static T checksetting(
    lua_State *L,
    const std::string& name,
    const T& default_) {

    T val;
    lua_getglobal(L, name.c_str());
    bool ok = check<T>(L, 1, val);
    lua_settop(L, 0);
    if (ok) {
        return val;
    }
    else {
        return default_;
    }
}

template <>
string SceneDescription::getsetting<string>(
    const string& name,
    const string& default_) const {

    return checksetting<string>(L, name, default_);
}

template <>
float SceneDescription::getsetting<float>(
    const string& name,
    const float& default_) const {

    return checksetting<float>(L, name, default_);
}

template <>
Vec3 SceneDescription::getsetting<Vec3>(
    const string& name,
    const Vec3& default_) const {

    return checksetting<Vec3>(L, name, default_);
}

template <>
string SceneDescription::getsetting<string>(
    const string& name) const {

    return checksetting<string>(L, name, "");
}

template <>
float SceneDescription::getsetting<float>(
    const std::string& name) const {

    return checksetting<float>(L, name, 0.0);
}

template <>
Vec3 SceneDescription::getsetting<Vec3>(
    const std::string& name) const {

    return checksetting<Vec3>(L, name, Vec3());
}

/*
template
Vec3 get_setting<Vec3>(string name) {
    load_global(this->L, name); // table
    lua_geti(this->L, 1, 1);    // table x
    lua_geti(this->L, 1, 2);    // table x y
    lua_geti(this->L, 1, 3);    // table x y z
    float x = luaL_checknumber(this->L, 2);
    float y = luaL_checknumber(this->L, 3);
    float z = luaL_checknumber(this->L, 4);
    lua_settop(this-L, 0);     // [empty]
    return Vec3(x, y, z);
}
*/
