#ifndef DEATHRAY_IMAGE_H_
#define DEATHRAY_IMAGE_H_

#include <iostream>
#include "color.h"

class Image
{
private:
    Color3u* data_;
    int height_, width_;

public:
    Image(int h, int w)
        : height_(h), width_(w)
    {
        data_ = new Color3u[w * h];
    }

    Image(Image&& other)
        : height_(other.height_), width_(other.width_), data_(other.data_)
    {
        other.data_ = nullptr;
    }

    ~Image()
    {
        delete[] data_;
    }

    Image& operator= (Image&& other)
    {
        if (this != &other) {
            delete[] data_;
            width_ = other.width_;
            height_ = other.height_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }

    inline Color3u& operator() (int i, int j)
    {
        return data_[width_ * i + j];
    }

    inline const Color3u& operator() (int i, int j) const
    {
        return data_[width_ * i + j];
    }

    inline int width() const { return width_; }
    inline int height() const { return height_; }

    void writePpmAscii(std::ostream& out) const;
    void writePpmBin(std::ostream& out) const;
};

#endif // DEATHRAY_IMAGE_HPP_
