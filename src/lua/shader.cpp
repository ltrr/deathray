#include "lua/shader.h"

#include "lua/op.h"
#include "shader/blinnphongshader.h"
#include "shader/depthshader.h"
#include "shader/normalshader.h"
#include "shader/raytracer.h"
#include "shader/toonshader.h"
#include "shader/bbox.h"


int shader_depth(lua_State* L)   // { foreground=, background=, maxdepth= }
{
    Vec3 fg, bg;
    float maxdepth;
    getintable(L, 1, "foreground", fg, Vec3(1,1,1));
    getintable(L, 1, "background", bg, Vec3(0,0,0));
    getintable(L, 1, "maxdepth", maxdepth, 1.0f);

    LuaOp<ShaderPtr>::newuserdata(L, new DepthShader(maxdepth, fg, bg));
    return 1;
}


int shader_normal(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new NormalShader());
    return 1;
}


int shader_blinnphong(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new BlinnPhongShader());
    return 1;
}


int shader_toon(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new ToonShader());
    return 1;
}


int shader_bbox(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new BBoxShader());
    return 1;
}


int shader_raytracer(lua_State* L)
{
    if (lua_gettop(L) == 0) {
        LuaOp<ShaderPtr>::newuserdata(L, new RayTracer());
    }
    else {
        int max_depth = LuaOp<int>::check(L, 1);
        LuaOp<ShaderPtr>::newuserdata(L, new RayTracer(max_depth));
    }
    return 1;
}


const luaL_Reg shader_lib[] = {
    { "depth", shader_depth },
    { "normal", shader_normal },
    { "blinnphong", shader_blinnphong },
    { "bbox", shader_bbox },
    { "toon", shader_toon },
    { "raytracer", shader_raytracer },
    { nullptr, nullptr }
};


int luaopen_shader(lua_State *L)
{
    luaL_newlib(L, shader_lib);
    return 1;
}
