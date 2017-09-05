#ifndef DEATHRAY_VIEWPORT_H
#define DEATHRAY_VIEWPORT_H

#include <memory>


class Viewport
{
private:
    int width_, height_;

public:
    Viewport()
        : width_(1), height_(1) {}

    Viewport(int w, int h)
        : width_(w), height_(h) {}

    int width()  { return width_; }
    int height() { return height_; }

    Vec3 pixelToWindow(float i, float j) const
    {
        return Vec3(j/width_, 1 -  i/height_, 1);
    }
};


typedef std::shared_ptr<Viewport> ViewportPtr;

#endif // DEATHRAY_VIEWPORT_H
