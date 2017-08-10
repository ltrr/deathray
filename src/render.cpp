#include <iostream>
#include <fstream>
#include <string>
#include "color.h"
#include "image.h"
#include "vector.h"
#include "ray.h"
#include "scene_description.h"
using std::string;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: render scenefile.lua" << std::endl;
        return 0;
    }

    SceneDescription sd = SceneDescription::fromfile(argv[1]);

    string name(sd.getsetting<string>("name"));
    string type(sd.getsetting<string>("type", "ppm"));
    string codification(sd.getsetting<string>("codification", "binary"));

    int cols(sd.getsetting<float>("width"));
    int rows(sd.getsetting<float>("height"));

    Color3f upper_left(sd.getsetting<Color3f>("upper_left"));
    Color3f lower_left(sd.getsetting<Color3f>("lower_left"));
    Color3f upper_right(sd.getsetting<Color3f>("upper_right"));
    Color3f lower_right(sd.getsetting<Color3f>("lower_right"));

    Image im(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float u = j / float(cols);
            float v = i / float(rows);
            im(i, j) = (1-v) * ((1-u) * upper_left + u * upper_right)
                       +  v  * ((1-u) * lower_left + u * lower_right);
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
