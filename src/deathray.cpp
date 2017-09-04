#include <cmath>
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include "color.h"
#include "image.h"
#include "vector.h"
#include "ray.h"
#include "scene_description.h"
#include "camera.h"
#include "viewport.h"
#include "object.h"
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
    SceneDescription sd = SceneDescription::fromfile(argv[1]);

    string name = sd.getsetting<string>("name");
    string type = sd.getsetting<string>("type", "ppm");
    string codification = sd.getsetting<string>("codification", "binary");

    RenderInfo info;
    info.viewport = sd.getsetting<ViewportPtr>("viewport");
    info.camera   = sd.getsetting<CameraPtr>("camera");
    info.scene    = sd.getsetting<ScenePtr>("scene");
    info.method   = sd.getsetting<RenderMethodPtr>("method", nullptr);
    if (!info.method) {
        info.method = RenderMethodPtr(new RayTracer());
    }
    info.num_samples = sd.getsetting<int>("samples", 1);

    //////// TEST ////////////////
    auto result = parseObj("suzane.obj");
    for (auto obj : result.objects) {
        info.scene->addobject(obj);
    }
    std::cerr << "obj count: " << result.objects.size() << '\n';

    //////////////////////////////

    Renderer renderer;
    Image image(renderer.render(info));

    if (codification == "binary") {
        std::ofstream out(name, std::ofstream::out | std::ofstream::binary);
        image.write_ppm_bin(out);
        out.close();
    }
    else {
        std::ofstream out(name, std::ofstream::out);
        image.write_ppm_ascii(out);
        out.close();
    }
    return 0;
}
