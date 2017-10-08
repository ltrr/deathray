#ifndef DEATHRAY_LUA_LIGHT_H_
#define DEATHRAY_LUA_LIGHT_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int light_light(lua_State *);

int light_spot(lua_State *);

int light_sun(lua_State *);

int luaopen_light(lua_State *);

extern const luaL_Reg light_lib[];


#endif // DEATHRAY_LUA_LIGHT_H_
