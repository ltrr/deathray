#include "lua/transform.h"
#include "lua/op.h"

#include "description/transformable.h"


int transform_eye(lua_State *L)   // { center, radius }
{

}


int transform_translate(lua_State *L)   // delta, obj | { objs }
{
    Vec3 delta = LuaOp<Vec3>::check(L, 1);

    TransformDescription *tr =
        new TransformDescription(Transform::translate(delta));

    if (lua_istable(L, 2)) {
        lua_len(L, 2);
        int len = lua_tointeger(L, 3);
        lua_pop(L, 1);

        for (int i = 1; i <= len; i++) {
            lua_geti(L, -1, i);              // ... table transf
            TransformableDescriptionPtr transformable =
                LuaOp<TransformableDescriptionPtr>::check(L, -1);
            tr->elements.push_back(transformable);
            lua_pop(L, 1);                   // ... table
        }
    }
    else if(LuaOp<TransformableDescriptionPtr>::is(L, 2)) {
        TransformableDescriptionPtr transformable =
            LuaOp<TransformableDescriptionPtr>::check(L, 2);
        tr->elements.push_back(transformable);
    }
    else {
        delete tr;
        luaL_error(L, "wrong arguments on translate");
        return 0;
    }

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, tr);
    return 1;
}


int transform_rotate(lua_State *L) // axis, angle, obj | {objs}
{
    Vec3 axis = LuaOp<Vec3>::check(L, 1);
    float angle = LuaOp<float>::check(L, 2);

    TransformDescription *tr =
        new TransformDescription(Transform::rotate(axis, angle));

    if (lua_istable(L, 3)) {
        lua_len(L, 3);
        int len = lua_tointeger(L, 4);
        lua_pop(L, 1);

        for (int i = 1; i <= len; i++) {
            lua_geti(L, -1, i);              // ... table transf
            TransformableDescriptionPtr transformable =
                LuaOp<TransformableDescriptionPtr>::check(L, -1);
            tr->elements.push_back(transformable);
            lua_pop(L, 1);                   // ... table
        }
    }
    else if(LuaOp<TransformableDescriptionPtr>::is(L, 3)) {
        TransformableDescriptionPtr transformable =
            LuaOp<TransformableDescriptionPtr>::check(L, 3);
        tr->elements.push_back(transformable);
    }
    else {
        delete tr;
        luaL_error(L, "wrong arguments on rotate");
        return 0;
    }

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, tr);
    return 1;
}


int transform_scale(lua_State *L)   // delta, obj | { objs }
{
    Vec3 scale = LuaOp<Vec3>::check(L, 1);

    TransformDescription *tr =
        new TransformDescription(Transform::scale(scale));

    if (lua_istable(L, 2)) {
        lua_len(L, 2);
        int len = lua_tointeger(L, 3);
        lua_pop(L, 1);

        for (int i = 1; i <= len; i++) {
            lua_geti(L, -1, i);              // ... table transf
            TransformableDescriptionPtr transformable =
                LuaOp<TransformableDescriptionPtr>::check(L, -1);
            tr->elements.push_back(transformable);
            lua_pop(L, 1);                   // ... table
        }
    }
    else if(LuaOp<TransformableDescriptionPtr>::is(L, 2)) {
        TransformableDescriptionPtr transformable =
            LuaOp<TransformableDescriptionPtr>::check(L, 2);
        tr->elements.push_back(transformable);
    }
    else {
        delete tr;
        luaL_error(L, "wrong arguments on scale");
        return 0;
    }

    LuaOp<TransformableDescriptionPtr>::newuserdata(L, tr);
    return 1;
}


const luaL_Reg transform_lib[] = {
    { "eye", transform_eye },
    { "translate", transform_translate },
    { "rotate", transform_rotate },
    { "scale", transform_scale },
    { nullptr, nullptr }
};


int luaopen_transform(lua_State *L)
{
    luaL_newlib(L, transform_lib);
    return 1;
}
