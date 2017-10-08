#include "lua/surface.h"

#include "lua/op.h"
#include "surface/sphere.h"
#include "surface/triangle.h"
#include "surface/spherevolume.h"
#include "util/objparser.h"


int surface_sphere(lua_State *L)   // { center, radius }
{
    Vec3 center;
    float radius;
    MaterialPtr mat;
    getintable(L, 1, "center", center);
    getintable(L, 1, "radius", radius);
    getintable(L, 1, "material", mat);

    LuaOp<SurfacePtr>::newuserdata(L, new Sphere(center, radius, mat));
    return 1;
}


int surface_spherevolume(lua_State *L)   // { center, radius }
{
    Vec3 center;
    float radius, d;
    MaterialPtr mat;
    getintable(L, 1, "center", center);
    getintable(L, 1, "radius", radius);
    getintable(L, 1, "density", d);
    getintable(L, 1, "material", mat);

    LuaOp<SurfacePtr>::newuserdata(L, new SphereVolume(center, radius, d, mat));
    return 1;
}


int surface_triangle(lua_State *L)   // { p1, p2, p3, material= }
{
    Vec3 p1, p2, p3;
    MaterialPtr mat;
    getintable(L, 1, 1, p1);
    getintable(L, 1, 2, p2);
    getintable(L, 1, 3, p3);
    getintable(L, 1, "material", mat);

    LuaOp<SurfacePtr>::newuserdata(L, new Triangle(p1, p2, p3, mat));
    return 1;
}


int surface_loadobj(lua_State *L)   // filename
{
    std::string filename(LuaOp<std::string>::check(L, 1));
    auto result = parseObj(filename);
    lua_settop(L, 0);                   //

    if (!result.ok) {
        luaL_error(L, "error reading mesh from file %s", filename.c_str());
    }

    lua_createtable(L, result.surfaces.size(), 0);               // table
    for (int i = 0; i < result.surfaces.size(); i++) {
        LuaOp<SurfacePtr>::pushuserdata(L, result.surfaces[i]);  // table surf
        lua_seti(L, 1, i+1);                                     // table
    }
    return 1;
}


const luaL_Reg surface_lib[] = {
    { "sphere", surface_sphere },
    { "triangle", surface_triangle },
    { "spherevolume", surface_spherevolume },
    { "loadobj", surface_loadobj },
    { nullptr, nullptr }
};


int luaopen_surface(lua_State *L)
{
    luaL_newlib(L, surface_lib);
    return 1;
}
