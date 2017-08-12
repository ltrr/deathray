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

    Color3f zenith_color = sd.getsetting<Color3f>("zenith_color");
    Color3f nadir_color = sd.getsetting<Color3f>("nadir_color");

    auto cam = sd.getsetting<shared_ptr<Camera>>("camera");

    auto obj = sd.getsetting<ScenePtr>("scene");

    // Init image
    Image im(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            Vec3 uv = viewport->pixeltowindow(i, j);
            Ray ray = cam->windowtoray(uv);

            float t = (1 + ray.dir().y) / 2;

            if (obj->hit(ray)) {
                im(i, j) = Color3f(1,0,0);
            }
            else {
                Color3f bgcolor = (1-t) * nadir_color + t * zenith_color;
                im(i, j) = bgcolor;
            }
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
