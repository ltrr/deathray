#include "image.hpp"

void Image::write_ppm(std::ostream& out) {
    out << "P3\n";
    out << w << " " << h << "\n";
    out << "255\n";
    for (int i = 0; i != h; i++) {
        for (int j = 0; j != w; j++) {
            Color4u c = (*this)(i, j);
            out << int(c.r) << " " << int(c.g) << " " << int(c.b) << " ";
        }
        out << "\n";
    }
}
