#include "util/image.h"


void Image::writePpmBin(std::ostream& out) const
{
    out << "P6\n";
    out << width_ << " " << height_ << "\n";
    out << "255\n";
    for (int i = 0; i != height_; i++) {
        for (int j = 0; j != width_; j++) {
            Color3u c = (*this)(i, j);
            out << c.r << c.g << c.b;
        }
    }
}


void Image::writePpmAscii(std::ostream& out) const
{
    out << "P3\n";
    out << width_ << " " << height_ << "\n";
    out << "255\n";
    for (int i = 0; i != height_; i++) {
        for (int j = 0; j != width_; j++) {
            Color3u c = (*this)(i, j);
            out << int(c.r) << ' '
                << int(c.g) << ' '
                << int(c.b) << ' ';
        }
        out << '\n';
    }
}
