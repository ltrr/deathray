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
#include "blue.h"
#include "raytracer.h"
#include "rendernormal.h"
#include "renderdepth.h"
using std::string;
using std::shared_ptr;

int main(int argc, char** argv)
{
    // Check args
    if (argc != 2) {
        std::cerr << "usage: render scenefile.lua" << std::endl;
        return 0;
    }

    // Load settings
    SceneDescription sd = SceneDescription::fromfile(argv[1]);

    string name = sd.getsetting<string>("name");
    string type = sd.getsetting<string>("type", "ppm");
    string codification = sd.getsetting<string>("codification", "binary");

    auto viewport = sd.getsetting<shared_ptr<Viewport>>("viewport");
    int rows = viewport->height();
    int cols = viewport->width();

    auto cam = sd.getsetting<shared_ptr<Camera>>("camera");
    auto scene = sd.getsetting<ScenePtr>("scene");
    auto method = sd.getsetting<RenderMethodPtr>("method", nullptr);
    if (!method) {
        method = RenderMethodPtr(new RayTracer());
    }

    int ns = sd.getsetting<int>("samples", 1);
    float* blue = getblue(ns);
    if (!blue) {
        std::cerr << "error: invalid number of samples ("
                  << ns << ")" << std::endl;
        exit(1);
    }

    // Init image
    Image im(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            Color3f color;
            for (int k = 0; k < ns; k++) {
                float id = i + blue[k << 1];
                float jd = j + blue[(k << 1) + 1];
                Vec3 uv = viewport->pixeltowindow(id, jd);
                Ray ray = cam->windowtoray(uv);
                //TODO: use correct gamma combination
                color += method->colorat(scene, ray);
            }
            color /= ns;
            im(i, j) = sqrt(color); // gamma correction
        }
    }

    if (codification == "binary") {
        std::ofstream out(name, std::ofstream::out | std::ofstream::binary);
        im.write_ppm_bin(out);
        out.close();
    }
    else {
        std::ofstream out(name, std::ofstream::out);
        im.write_ppm_ascii(out);
        out.close();
    }
    return 0;
}
