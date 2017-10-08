#ifndef DEATHRAY_LUA_MATERIAL_H_
#define DEATHRAY_LUA_MATERIAL_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int material_lambertian(lua_State *);

int material_metal(lua_State *);

int material_dieletric(lua_State *);

int material_toon(lua_State *);

int material_blinnphong(lua_State *);

int luaopen_material(lua_State *);

extern const luaL_Reg material_lib[];

#endif // DEATHRAY_LUA_MATERIAL_H_
