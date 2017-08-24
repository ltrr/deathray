#ifndef DEATHRAY_IMAGE_H_
#define DEATHRAY_IMAGE_H_

#include <iostream>
#include "color.h"

class Image {
private:
    Color3u* data;
    int h, w;

public:
    Image(int h, int w) : h(h), w(w)
    {
        data = new Color3u[w * h];
    }

    ~Image()
    {
        delete[] data;
    }

    Image(Image&& other) : h(other.h), w(other.w), data(other.data)
    {
        other.data = nullptr;
    }

    Image& operator= (Image&& other)
    {
        if (this != &other) {
            delete[] data;
            w = other.w;
            h = other.h;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    inline Color3u& operator() (int i, int j)
    {
        return data[w * i + j];
    }

    inline Color3u operator() (int i, int j) const
    {
        return data[w * i + j];
    }

    inline int width() const { return w; }
    inline int height() const { return h; }

    void write_ppm_ascii(std::ostream& out) const;
    void write_ppm_bin(std::ostream& out) const;
};

#endif // DEATHRAY_IMAGE_HPP_
