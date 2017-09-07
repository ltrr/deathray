#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "scene/scenedescription.h"
#include "scene/camera.h"
#include "scene/viewport.h"
#include "scene/renderer.h"
#include "scene/scene.h"
#include "shader/raytracer.h"
#include "util/image.h"
#include "util/progressbar.h"
using std::string;
using std::shared_ptr;


void render(char* filename)
{
    // Load settings
    SceneDescription sd = SceneDescription::fromFile(filename);

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

    ProgressBar progress;
    progress.start(filename, info);

    Renderer renderer;
    Image image(renderer.render(info, progress));

    progress.finish();

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
}


int main(int argc, char** argv)
{
    // Check args
    if (argc < 2) {
        std::cerr << "usage: deathray scenefile.lua [...]" << std::endl;
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        render(argv[i]);
    }

    return 0;
}
