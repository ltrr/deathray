#ifndef DEATHRAY_LUA_TEXTURE_H_
#define DEATHRAY_LUA_TEXTURE_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int texture_color(lua_State *);

int luaopen_texture(lua_State *);

extern const luaL_Reg texture_lib[];

#endif // DEATHRAY_LUA_TEXTURE_H_
