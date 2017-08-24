#ifndef DEATHRAY_VIEWPORT_H
#define DEATHRAY_VIEWPORT_H

#include <memory>


class Viewport
{
private:
    int w, h;

public:
    Viewport() : w(1), h(1) {}

    Viewport(int w, int h) : w(w), h(h) {}

    int width()  { return w; }
    int height() { return h; }

    Vec3 pixeltowindow(float i, float j) const
    {
        return Vec3(j/w, 1 -  i/h, 1);
    }
};


typedef std::shared_ptr<Viewport> ViewportPtr;

#endif // DEATHRAY_VIEWPORT_H
