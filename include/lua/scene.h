#ifndef DEATHRAY_LUASCENE_H_
#define DEATHRAY_LUASCENE_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int scene_lookat(lua_State* L);

int scene_mkviewport(lua_State* L);

int scene_mksky(lua_State* L);

int scene_mkscene(lua_State* L);

int luaopen_scene(lua_State* L);

extern const luaL_Reg scene_lib[];

#endif // DEATHRAY_LUASCENE_H_
