#ifndef DEATHRAY_LUAOP_H_
#define DEATHRAY_LUAOP_H_

#include <memory>
#include <string>
#include <new>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "light/light.h"
#include "material/material.h"
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/viewport.h"
#include "shader/shader.h"
#include "texture/texture.h"
#include "util/outputconfig.h"
#include "util/vector.h"


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
struct UserType<Texture>
{
    static constexpr const char* name = "texture";
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


template<>
struct UserType<OutputConfig>
{
    static constexpr const char* name = "outputconfig";
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
struct LuaOp<std::string>
{
    static std::string check(lua_State *L, int idx)
    {
        return std::string(luaL_checkstring(L, idx));
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
struct LuaOp<std::shared_ptr<T>>
{
    static_assert(UserType<T>::name != nullptr,
                 "std::shared_ptr operations requires named type");

    static std::shared_ptr<T> check(lua_State *L, int idx)
    {
        return *((std::shared_ptr<T> *) luaL_checkudata(L, idx, UserType<T>::name));
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
        auto p = (std::shared_ptr<T> *) luaL_checkudata(L, 1, UserType<T>::name);
        p->reset();
        return 0;
    }

    static std::shared_ptr<T> newuserdata(lua_State *L, T *p)
    {
        void *addr = lua_newuserdata(L, sizeof(std::shared_ptr<T>));
        auto *addr_ = new (addr) std::shared_ptr<T>(p);
        luaL_setmetatable(L, UserType<T>::name);
        return *addr_;
    }

    static std::shared_ptr<T> pushuserdata(lua_State *L, std::shared_ptr<T> p)
    {
        void *addr = lua_newuserdata(L, sizeof(std::shared_ptr<T>));
        auto *addr_ = new (addr) std::shared_ptr<T>(p);
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


#endif // DEATHRAY_LUAOP_H_
