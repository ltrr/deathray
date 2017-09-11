#ifndef DEATHRAY_LUASCENE_H_
#define DEATHRAY_LUASCENE_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int scene_lookat(lua_State* L);

int scene_mkviewport(lua_State* L);

int scene_mklambert(lua_State* L);

int scene_mkmetal(lua_State* L);

int scene_mkblinnphong(lua_State* L);

int scene_mksphere(lua_State* L);

int scene_mktriangle(lua_State* L);

int scene_loadobj(lua_State* L);

int scene_mkpointlight(lua_State* L);

int scene_mksun(lua_State* L);

int scene_mksky(lua_State* L);

int scene_mkdepthrender(lua_State* L);

int scene_mknormalrender(lua_State* L);

int scene_mkblinnphongshader(lua_State* L);

int scene_mkscene(lua_State* L);

int luaopen_scene(lua_State* L);

extern luaL_Reg scene_lib[];

#endif // DEATHRAY_LUASCENE_H_
