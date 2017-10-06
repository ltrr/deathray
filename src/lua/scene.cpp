#include "lua/scene.h"

#include <type_traits>
#include "background/sky.h"
#include "surface/sphere.h"
#include "surface/spherevolume.h"
#include "surface/triangle.h"
#include "material/blinnphong.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "light/sun.h"
#include "lua/op.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dieletric.h"
#include "material/toon.h"
#include "shader/normalshader.h"
#include "shader/depthshader.h"
#include "shader/raytracer.h"
#include "shader/blinnphongshader.h"
#include "shader/toonshader.h"
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


int scene_mklambert(lua_State* L)   // albedo
{
    if (LuaOp<Vec3>::is(L, 1)) {
        Vec3 albedo = LuaOp<Vec3>::check(L, 1); // albedo
        lua_pop(L, 1);                          //
        LuaOp<MaterialPtr>::newuserdata(L, new Lambertian(albedo));
    }
    else {
        Vec3 albedo, emission;
        getintable(L, 1, "albedo", albedo);
        getintable(L, 1, "emission", emission, Vec3(0,0,0));
        lua_pop(L, 1);                          //
        LuaOp<MaterialPtr>::newuserdata(L, new Lambertian(albedo, emission));
    }

    return 1;
}


int scene_mkmetal(lua_State* L)   // { albedo=, fuzz= }
{
    Vec3 albedo, emission;
    float fuzz;
    getintable(L, 1, "albedo", albedo);
    getintable(L, 1, "fuzz", fuzz, 0.0f);
    getintable(L, 1, "emission", emission, Vec3(0,0,0));

    LuaOp<MaterialPtr>::newuserdata(L, new Metal(albedo, fuzz, emission));
    return 1;
}


int scene_mkdieletric(lua_State* L)   // { albedo=, fuzz= }
{
    float ref_idx;
    getintable(L, 1, "ref_idx", ref_idx);

    LuaOp<MaterialPtr>::newuserdata(L, new Dieletric(ref_idx));
    return 1;
}


int scene_mktoon(lua_State* L)
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

    LuaOp<MaterialPtr>::newuserdata(L, new Toon(colors, cuts));
    return 1;
}


int scene_mkblinnphong(lua_State* L)   // { albedo=, fuzz= }
{
    Vec3 specular, diffuse, ambient;
    float shiness;
    getintable(L, 1, "specular", specular, Vec3(0,0,0));
    getintable(L, 1, "diffuse", diffuse, Vec3(0,0,0));
    getintable(L, 1, "ambient", ambient, Vec3(0,0,0));
    getintable(L, 1, "shiness", shiness, 0.0f);

    LuaOp<MaterialPtr>::newuserdata(L,
        new BlinnPhong(diffuse, specular, ambient, shiness));
    return 1;
}


int scene_mksphere(lua_State* L)   // { center, radius }
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


int scene_mkspherevolume(lua_State* L)   // { center, radius }
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


int scene_mktriangle(lua_State* L)   // { p1, p2, p3, material= }
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


int scene_loadobj(lua_State* L)   // filename
{
    string filename(LuaOp<string>::check(L, 1));
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


int scene_mkpointlight(lua_State* L)
{
    Vec3 position, intensity;
    getintable(L, 1, "position", position);
    getintable(L, 1, "intensity", intensity);

    LuaOp<LightPtr>::newuserdata(L, new PointLight(position, intensity));
    return 1;
}


int scene_mkspotlight(lua_State* L)
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


int scene_mksun(lua_State* L)
{
    Vec3 direction, intensity;
    getintable(L, 1, "direction", direction);
    getintable(L, 1, "intensity", intensity);

    LuaOp<LightPtr>::newuserdata(L, new Sun(direction, intensity));
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


int scene_mkdepthrender(lua_State* L)   // { foreground=, background=, maxdepth= }
{
    Vec3 fg, bg;
    float maxdepth;
    getintable(L, 1, "foreground", fg, Vec3(1,1,1));
    getintable(L, 1, "background", bg, Vec3(0,0,0));
    getintable(L, 1, "maxdepth", maxdepth, 1.0f);

    LuaOp<ShaderPtr>::newuserdata(L, new DepthShader(maxdepth, fg, bg));
    return 1;
}


int scene_mknormalrender(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new NormalShader());
    return 1;
}


int scene_mkblinnphongshader(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new BlinnPhongShader());
    return 1;
}


int scene_mktoonshader(lua_State* L)
{
    LuaOp<ShaderPtr>::newuserdata(L, new ToonShader());
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
        shader = ShaderPtr(new RayTracer);
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


luaL_Reg scene_lib[] = {
    { "lookat", scene_lookat },
    { "mkviewport", scene_mkviewport },
    { "sphere", scene_mksphere },
    { "sphere_volume", scene_mkspherevolume },
    { "triangle", scene_mktriangle },
    { "loadobj", scene_loadobj },
    { "lambert", scene_mklambert },
    { "dieletric", scene_mkdieletric },
    { "metal", scene_mkmetal },
    { "blinn_phong", scene_mkblinnphong },
    { "toon", scene_mktoon },
    { "sky", scene_mksky },
    { "spotlight", scene_mkspotlight },
    { "pointlight", scene_mkpointlight },
    { "sun", scene_mksun },
    { "depthshader", scene_mkdepthrender },
    { "normalshader", scene_mknormalrender },
    { "toon_shader", scene_mktoonshader },
    { "blinn_phong_shader", scene_mkblinnphongshader },
    { "mkscene", scene_mkscene },
    { "output_config", scene_mkoutputconfig },
    { nullptr, nullptr }
};


int luaopen_scene(lua_State* L)
{
    LuaOp<ScenePtr>::registerudata(L);
    LuaOp<CameraPtr>::registerudata(L);
    LuaOp<ViewportPtr>::registerudata(L);
    LuaOp<SurfacePtr>::registerudata(L);
    LuaOp<MaterialPtr>::registerudata(L);
    LuaOp<BackgroundPtr>::registerudata(L);
    LuaOp<ShaderPtr>::registerudata(L);
    LuaOp<LightPtr>::registerudata(L);
    LuaOp<OutputConfigPtr>::registerudata(L);

    lua_getglobal(L, "_G");           // _G
    luaL_setfuncs(L, scene_lib, 0);   // _G
    lua_pop(L, 1);                    //
    return 0;
}
