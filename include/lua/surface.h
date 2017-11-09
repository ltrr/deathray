#ifndef DEATHRAY_LUA_SURFACE_H_
#define DEATHRAY_LUA_SURFACE_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int surface_sphere(lua_State *);

int surface_triangle(lua_State *);

int surface_plane(lua_State *);

//int surface_spherevolume(lua_State *);

int surface_loadobj(lua_State *);

int luaopen_surface(lua_State *);

extern const luaL_Reg surface_lib[];

#endif // DEATHRAY_LUA_SURFACE_H_
