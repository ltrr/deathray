#include "lua/scene.h"

#include <type_traits>
#include "background/sky.h"
#include "lua/op.h"
#include "lua/light.h"
#include "lua/material.h"
#include "lua/shader.h"
#include "lua/surface.h"
#include "lua/texture.h"
#include "util/objparser.h"
using std::string;


int scene_lookat(lua_State* L)
{
    Vec3 origin, target, up;
    float aspect, fov;
    getintable(L, 1, "origin", origin);
    getintable(L, 1, "target", target);
    getintable(L, 1, "up", up);
    getintable(L, 1, "aspect", aspect);
    getintable(L, 1, "fov", fov);

    LuaOp<CameraPtr>::newuserdata(L, new PerspectiveCamera(origin, target, up, fov, aspect));
    return 1;
}


int scene_mkviewport(lua_State* L)  // { width=, height= }
{
    int width, height;
    getintable(L, 1, "width", width);
    getintable(L, 1, "height", height);

    LuaOp<ViewportPtr>::newuserdata(L, new Viewport(width, height));
    return 1;
}


int scene_mksky(lua_State* L)   // { zenith, nadir }
{
    Vec3 zenith, nadir;
    getintable(L, 1, "zenith", zenith);
    getintable(L, 1, "nadir", nadir);

    LuaOp<BackgroundPtr>::newuserdata(L, new Sky(zenith, nadir));
    return 1;
}


int scene_mkoutputconfig(lua_State* L)
{
    string file, format, codif;
    getintable(L, 1, "filename", file);
    getintable(L, 1, "format", format);
    getintable(L, 1, "codification", codif);

    auto iformat = (ImageFormat::PPM);
    auto icodif = (codif == "ascii" ?
        ImageCodification::ASCII : ImageCodification::BINARY);

    LuaOp<OutputConfigPtr>::newuserdata(L,
        new OutputConfig(file, iformat, icodif));
    return 1;
}


void add_surfaces(lua_State* L, Scene* scene) // ... (table|obj)
{
    if (lua_istable(L, -1)) {                        // ... table
        lua_len(L, -1);                               // ... table len
        int len = lua_tointeger(L, -1);              // ... table len
        lua_pop(L, 1);                               // ... table
        for (int i = 1; i <= len; i++) {
            lua_geti(L, -1, i);                      // ... table (table|obj)
            add_surfaces(L, scene);                  // ... table (table|obj)
            lua_pop(L, 1);                           // ... table
        }
    }
    else if (LuaOp<SurfacePtr>::is(L, -1)) {
        SurfacePtr surface = LuaOp<SurfacePtr>::check(L, -1);  // table surf
        scene->addSurface(surface);                            // table surf
    }
    else if(LuaOp<LightPtr>::is(L, -1)) {
        LightPtr light = LuaOp<LightPtr>::check(L, -1);        // table light
        scene->addLight(light);                                // table light
    }
}


int scene_mkscene(lua_State* L) // { obj1, obj2, {objs}, ..., bg = }
{
    Color3f ambient;
    getintable(L, 1, "ambient", ambient, Vec3(0,0,0));

    BackgroundPtr bg;
    getintable(L, 1, "bg", bg, BackgroundPtr());
    if (!bg) {
        bg = BackgroundPtr(new Sky);
    }

    ViewportPtr viewport;
    getintable(L, 1, "viewport", viewport);

    CameraPtr camera;
    getintable(L, 1, "camera", camera);

    int sample_count;
    getintable(L, 1, "samples", sample_count, 1);

    OutputConfigPtr config;
    getintable(L, 1, "output_config", config);

    ShaderPtr shader;
    getintable(L, 1, "shader", shader);
    if (!shader) {
        lua_pushcfunction(L, shader_raytracer);
        lua_call(L, 0, 1);
        shader = LuaOp<ShaderPtr>::check(L, -1);
        lua_pop(L, 1);
    }

    Scene *newscene = new Scene();
    newscene->ambient() = ambient;
    newscene->background() = bg;
    newscene->viewport() = viewport;
    newscene->camera() = camera;
    newscene->sampleCount() = sample_count;
    newscene->outputConfig() = config;
    newscene->shader() = shader;

    add_surfaces(L, newscene);                 // {objs}
    lua_settop(L, 0);                          //
    LuaOp<ScenePtr>::newuserdata(L, newscene); // scene
    return 1;
}


const luaL_Reg scene_lib[] = {
    { "lookat", scene_lookat },
    { "mkviewport", scene_mkviewport },
    { "sky", scene_mksky },
    { "mkscene", scene_mkscene },
    { "output_config", scene_mkoutputconfig },
    { nullptr, nullptr }
};


// Transfer value from table on position -1 to table on position -2,
// with the same name
static void transfer(lua_State *L, const char* name)
{
    // t1 t2
    lua_pushstring(L, name); // t1 t2 name
    lua_pushvalue(L, -1);    // t1 t2 name name
    lua_gettable(L, -3);     // t1 t2 name obj
    lua_settable(L, -4);     // t1 t2
}


int luaopen_scene(lua_State* L)
{
    LuaOp<ScenePtr>::registerudata(L);
    LuaOp<CameraPtr>::registerudata(L);
    LuaOp<ViewportPtr>::registerudata(L);
    LuaOp<SurfacePtr>::registerudata(L);
    LuaOp<MaterialPtr>::registerudata(L);
    LuaOp<TexturePtr>::registerudata(L);
    LuaOp<BackgroundPtr>::registerudata(L);
    LuaOp<ShaderPtr>::registerudata(L);
    LuaOp<LightPtr>::registerudata(L);
    LuaOp<OutputConfigPtr>::registerudata(L);

    lua_getglobal(L, "_G");           // _G
    luaL_setfuncs(L, scene_lib, 0);   // _G

    luaopen_material(L);              // _G mat
    lua_pushstring(L, "material");    // _G mat "mat"
    lua_pushvalue(L, -2);             // _G mat "mat" mat
    lua_settable(L, 1);               // _G mat
    transfer(L, "metal");
    transfer(L, "lambertian");
    transfer(L, "dieletric");
    transfer(L, "blinnphong");
    transfer(L, "toon");
    lua_pop(L, 1);                    // _G

    luaopen_shader(L);                // _G shader
    lua_setglobal(L, "shader");       // _G

    luaopen_light(L);                 // _G light
    lua_setglobal(L, "light");        // _G

    luaopen_surface(L);              // _G mat
    lua_pushstring(L, "surface");    // _G mat "mat"
    lua_pushvalue(L, -2);             // _G mat "mat" mat
    lua_settable(L, 1);               // _G mat
    transfer(L, "triangle");
    transfer(L, "sphere");
    transfer(L, "spherevolume");
    transfer(L, "loadobj");
    lua_pop(L, 1);                    // _G

    luaopen_texture(L);               // _G tex
    lua_pushstring(L, "texture");     // _G tex "tex"
    lua_pushvalue(L, -2);             // _G tex "tex" tex
    lua_settable(L, 1);               // _G tex
    transfer(L, "color");
    lua_pop(L, 1);                    // _G

    return 0;
}
