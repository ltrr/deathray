#include "lua/shader.h"

#include "lua/op.h"
#include "description/light.h"
//#include "light/pointlight.h"
//#include "light/spotlight.h"
//#include "light/sun.h"


int light_point(lua_State* L)
{
    PointLightDescription *light = new PointLightDescription();
    getintable(L, 1, "position", light->position);
    getintable(L, 1, "intensity", light->intensity);

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, light);
    return 1;
}


int light_spot(lua_State* L)
{
    SpotLightDescription *light = new SpotLightDescription();

    getintable(L, 1, "position", light->position);
    getintable(L, 1, "direction", light->direction);
    getintable(L, 1, "intensity", light->intensity);
    getintable(L, 1, "angle", light->angle);
    getintable(L, 1, "decay", light->decay, 1.0f);

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, light);
    return 1;
}


int light_sun(lua_State* L)
{
    DirectionalLightDescription *light = new DirectionalLightDescription();

    getintable(L, 1, "direction", light->direction);
    getintable(L, 1, "intensity", light->intensity);

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, light);
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
