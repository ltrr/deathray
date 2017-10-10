#include "lua/material.h"

#include "lua/op.h"
#include "material/blinnphong.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dieletric.h"
#include "material/toon.h"


int material_lambertian(lua_State* L)   // albedo
{
    if (LuaOp<TexturePtr>::is(L, 1)) {
        TexturePtr albedo = LuaOp<TexturePtr>::check(L, 1); // albedo
        lua_pop(L, 1);                          //
        LuaOp<MaterialPtr>::newuserdata(L, new Lambertian(albedo));
    }
    else {
        TexturePtr albedo, emission;
        getintable(L, 1, "albedo", albedo, WHITE_TEXTURE);
        getintable(L, 1, "emission", emission, BLACK_TEXTURE);
        lua_pop(L, 1);                          //
        LuaOp<MaterialPtr>::newuserdata(L, new Lambertian(albedo, emission));
    }

    return 1;
}


int material_metal(lua_State* L)   // { albedo=, fuzz= }
{
    TexturePtr albedo, emission;
    float fuzz;
    getintable(L, 1, "albedo", albedo);
    getintable(L, 1, "fuzz", fuzz, 0.0f);
    getintable(L, 1, "emission", emission, BLACK_TEXTURE);

    LuaOp<MaterialPtr>::newuserdata(L, new Metal(albedo, fuzz, emission));
    return 1;
}


int material_dieletric(lua_State* L)   // { albedo=, fuzz= }
{
    float ref_idx;
    getintable(L, 1, "ref_idx", ref_idx);

    LuaOp<MaterialPtr>::newuserdata(L, new Dieletric(ref_idx));
    return 1;
}


int material_toon(lua_State* L)
{
    std::vector<Color3f> colors;
    std::vector<float> cuts;

    lua_len(L, 1);                              // table len
    int len = lua_tointeger(L, -1);              // table len
    lua_pop(L, 1);                               // table

    Color3f color;
    float cut;

    getintable(L, 1, 1, color);
    colors.push_back(color);
    for (int i = 2; i <= len; i += 2) {
        getintable(L, 1, i, cut);
        cuts.push_back(cut);
        getintable(L, 1, i+1, color);
        colors.push_back(color);
    }

    LuaOp<MaterialPtr>::newuserdata(L, new ToonMaterial(colors, cuts));
    return 1;
}


int material_blinnphong(lua_State* L)   // { albedo=, fuzz= }
{
    Vec3 specular, diffuse, ambient;
    float shininess;
    getintable(L, 1, "specular", specular, Vec3(0,0,0));
    getintable(L, 1, "diffuse", diffuse, Vec3(0,0,0));
    getintable(L, 1, "ambient", ambient, Vec3(0,0,0));
    getintable(L, 1, "shininess", shininess, 0.0f);

    LuaOp<MaterialPtr>::newuserdata(L,
        new BlinnPhongMaterial(diffuse, specular, ambient, shininess));
    return 1;
}


const luaL_Reg material_lib[] = {
    { "lambertian", material_lambertian },
    { "metal", material_metal },
    { "dieletric", material_dieletric },
    { "toon", material_toon },
    { "blinnphong", material_blinnphong },
    { nullptr, nullptr }
};


int luaopen_material(lua_State *L)
{
    luaL_newlib(L, material_lib);
    return 1;
}
