#ifndef DEATHRAY_LUA_SHADER_H_
#define DEATHRAY_LUA_SHADER_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int shader_blinnphong(lua_State *);

int shader_depth(lua_State *);

int shader_normal(lua_State *);

int shader_raytracer(lua_State *);

int luaopen_shader(lua_State *);

extern const luaL_Reg shader_lib[];

#endif // DEATHRAY_LUA_SHADER_H_
