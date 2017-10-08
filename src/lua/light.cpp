#include "lua/shader.h"

#include "lua/op.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "light/sun.h"


int light_point(lua_State* L)
{
    Vec3 position, intensity;
    getintable(L, 1, "position", position);
    getintable(L, 1, "intensity", intensity);

    LuaOp<LightPtr>::newuserdata(L, new PointLight(position, intensity));
    return 1;
}


int light_spot(lua_State* L)
{
    Vec3 position, direction, intensity;
    float angle, decay;

    getintable(L, 1, "position", position);
    getintable(L, 1, "direction", direction);
    getintable(L, 1, "intensity", intensity);
    getintable(L, 1, "angle", angle);
    getintable(L, 1, "decay", decay, 1.0f);

    LuaOp<LightPtr>::newuserdata(L, new SpotLight(position, direction,
        intensity, angle, decay));
    return 1;
}


int light_sun(lua_State* L)
{
    Vec3 direction, intensity;
    getintable(L, 1, "direction", direction);
    getintable(L, 1, "intensity", intensity);

    LuaOp<LightPtr>::newuserdata(L, new Sun(direction, intensity));
    return 1;
}


const luaL_Reg light_lib[] = {
    { "point", light_point },
    { "spot", light_spot },
    { "sun", light_sun },
    { nullptr, nullptr }
};


int luaopen_light(lua_State *L)
{
    luaL_newlib(L, light_lib);
    return 1;
}
