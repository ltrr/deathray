#include "lua/surface.h"

#include "lua/op.h"
#include "surface/sphere.h"
#include "surface/triangle.h"
#include "surface/spherevolume.h"
#include "util/objparser.h"


int surface_sphere(lua_State *L)   // { center, radius }
{
    SphereDescription *surf = new SphereDescription();

    getintable(L, 1, "center", surf->center);
    getintable(L, 1, "radius", surf->radius);
    getintable(L, 1, "material", surf->material);

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, surf);
    return 1;
}


int surface_triangle(lua_State *L)   // { p1, p2, p3, material= }
{
    TriangleDescription *surf = new TriangleDescription();

    getintable(L, 1, 1, surf->p0);
    getintable(L, 1, 2, surf->p1);
    getintable(L, 1, 3, surf->p2);
    getintable(L, 1, "material", surf->material);

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, surf);
    return 1;
}


int surface_loadobj(lua_State *L)   // filename
{
    std::string filename(LuaOp<std::string>::check(L, 1));

    MeshDescription *surf = new MeshDescription;

    bool ok = parseObj(filename, surf);
    lua_settop(L, 0);                   //

    if (!ok) {
        luaL_error(L, "error reading mesh from file %s", filename.c_str());
        delete surf;
        return 0;
    }
    else {
        LuaOp<TransformableDescriptionPtr>::newuserdata(L, surf);
        return 1;
    }
}


const luaL_Reg surface_lib[] = {
    { "sphere", surface_sphere },
    { "triangle", surface_triangle },
    { "loadobj", surface_loadobj },
    { nullptr, nullptr }
};


int luaopen_surface(lua_State *L)
{
    luaL_newlib(L, surface_lib);
    return 1;
}
