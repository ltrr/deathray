#ifndef DEATHRAY_IMAGE_H_
#define DEATHRAY_IMAGE_H_

#include <iostream>
#include "color.h"

class Image {
private:
    Color3u* data;
    int h, w;

public:

    Image(int h, int w) : h(h), w(w) {
        data = new Color3u[w * h];
    }

    ~Image() {
        delete[] data;
    }

    Color3u& operator() (int i, int j) {
        return data[w * i + j];
    }

    int width() const { return w; }
    int height() const { return h; }

    void write_ppm_ascii(std::ostream& out);
    void write_ppm_bin(std::ostream& out);
};

#endif // DEATHRAY_IMAGE_HPP_
