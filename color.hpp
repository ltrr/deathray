#ifndef RAYTRACER_COLOR_HPP_
#define RAYTRACER_COLOR_HPP_

#include <algorithm>
#include <cstdint>
using std::min;
using std::max;

uint8_t ftu8(float x);
float u8tf(uint8_t x);

class Color4u;

class Color4f {
public:
    float r, g, b, a;
    Color4f()
        : r(0.0), g(0.0), b(0.0), a(1.0) {}
    Color4f(float r, float g, float b)
        : r(r), g(g), b(b), a(1.0) {}
    Color4f(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a) {}
    Color4f(const Color4f& c)
        : r(c.r), g(c.g), b(c.b), a(c.a) {}
    Color4f(const Color4u& c);
};

class Color4u {
public:
    uint8_t r, g, b, a;
    Color4u()
        : r(0), g(0), b(0), a(255) {}
    Color4u(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b), a(255) {}
    Color4u(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r(r), g(g), b(b), a(a) {}
    Color4u(const Color4u& c)
        : r(c.r), g(c.g), b(c.b), a(c.a) {}
    Color4u(const Color4f& c);
};

#endif // RAYTRACER_COLOR_HPP_
