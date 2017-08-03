#ifndef RAYTRACER_IMAGE_HPP_
#define RAYTRACER_IMAGE_HPP_

#include <iostream>
#include "color.hpp"

class Image {
private:
    Color4u* data;
    int h, w;

public:

    Image(int h, int w) : h(h), w(w) {
        data = new Color4u[w * h];
    }

    ~Image() {
        delete[] data;
    }

    Color4u& operator() (int i, int j) {
        return data[w * i + j];
    }

    int width() const { return w; }
    int height() const { return h; }

    void write_ppm(std::ostream& out);
};

#endif // RAYTRACER_IMAGE_HPP_
