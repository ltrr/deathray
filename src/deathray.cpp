#include <cmath>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include "color.h"
#include "image.h"
#include "vector.h"
#include "ray.h"
#include "scenedescription.h"
#include "camera.h"
#include "viewport.h"
#include "surface.h"
#include "sphere.h"
#include "scene.h"
#include "raytracer.h"
#include "renderer.h"
#include "objparser.h"
using std::string;
using std::shared_ptr;

int main(int argc, char** argv)
{
    // Check args
    if (argc != 2) {
        std::cerr << "usage: deathray scenefile.lua" << std::endl;
        return 0;
    }

    // Load settings
    SceneDescription sd = SceneDescription::fromFile(argv[1]);

    string name = sd.getSetting<string>("name");
    string type = sd.getSetting<string>("type", "ppm");
    string codification = sd.getSetting<string>("codification", "binary");

    RenderInfo info;
    info.viewport = sd.getSetting<ViewportPtr>("viewport");
    info.camera   = sd.getSetting<CameraPtr>("camera");
    info.scene    = sd.getSetting<ScenePtr>("scene");
    info.shader   = sd.getSetting<ShaderPtr>("shader", nullptr);
    if (!info.shader) {
        info.shader = ShaderPtr(new RayTracer());
    }
    info.num_samples = sd.getSetting<int>("samples", 1);


    Renderer renderer;
    Image image(renderer.render(info));

    if (codification == "binary") {
        std::ofstream out(name, std::ofstream::out | std::ofstream::binary);
        image.writePpmBin(out);
        out.close();
    }
    else {
        std::ofstream out(name, std::ofstream::out);
        image.writePpmAscii(out);
        out.close();
    }
    return 0;
}
