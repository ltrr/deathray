#include "image.h"

void Image::write_ppm_bin(std::ostream& out) {
    out << "P6\n";
    out << w << " " << h << "\n";
    out << "255\n";
    for (int i = 0; i != h; i++) {
        for (int j = 0; j != w; j++) {
            Color3u c = (*this)(i, j);
            out << c.r << c.g << c.b;
        }
    }
}

void Image::write_ppm_ascii(std::ostream& out) {
    out << "P3\n";
    out << w << " " << h << "\n";
    out << "255\n";
    for (int i = 0; i != h; i++) {
        for (int j = 0; j != w; j++) {
            Color3u c = (*this)(i, j);
            out << int(c.r) << ' '
                << int(c.g) << ' '
                << int(c.b) << ' ';
        }
        out << '\n';
    }
}
