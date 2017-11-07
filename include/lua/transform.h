#ifndef DEATHRAY_LUA_TRANSFORM_H_
#define DEATHRAY_LUA_TRANSFORM_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int transform_eye(lua_State *);

int transform_translate(lua_State *);

int transform_rotate(lua_State *);

int transform_scale(lua_State *);

int luaopen_transform(lua_State *);

extern const luaL_Reg transform_lib[];

#endif // DEATHRAY_LUA_TRANSFORM_H_
