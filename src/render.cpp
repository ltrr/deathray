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
//#include "cameraviewport.h"
using std::string;
using std::shared_ptr;

bool hit_sphere(const Ray &r, const Point3 &c, float radius)
{
    Vec3 co = r.origin() - c;
    float A = len2(r.dir());
    float B = 2*dot(co, r.dir());
    float C = len2(co) - radius * radius;

    return (B*B - 4*A*C) >= 0;
}

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
    int rows = viewport->width();
    int cols = viewport->height();

    Color3f zenith_color = sd.getsetting<Color3f>("zenith_color");
    Color3f nadir_color = sd.getsetting<Color3f>("nadir_color");

    auto cam = sd.getsetting<shared_ptr<Camera>>("camera");

    Vec3 center(2, 0, 0);
    float radius = 0.3;

    // Init image
    Image im(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            Vec3 uv = viewport->pixeltowindow(i, j);
            Ray ray = cam->windowtoray(uv);

            float t = (1 + ray.dir().y) / 2;

            if (hit_sphere(ray, center, radius)) {
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
