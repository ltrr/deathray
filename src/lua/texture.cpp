#include "lua/texture.h"

#include "lua/op.h"
#include "texture/texture.h"
#include "texture/checkers.h"
#include "util/color.h"


int texture_color(lua_State *L)   // rgb
{
    Color3f color = LuaOp<Color3f>::check(L, 1);
    LuaOp<TexturePtr>::newuserdata(L, new ConstTexture(color));
    return 1;
}


int texture_checkers(lua_State *L)
{
    LuaOp<TexturePtr>::newuserdata(L, new CheckersTexture);
    return 1;
}


const luaL_Reg texture_lib[] = {
    { "color", texture_color },
    { "checkers", texture_checkers },
    { nullptr, nullptr }
};


int luaopen_texture(lua_State *L)
{
    luaL_newlib(L, texture_lib);
    return 1;
}
