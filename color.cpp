#include "color.hpp"

uint8_t ftu8(float x) {
    return max(0, min(255, int(256 * x)));
}

float u8tf(uint8_t x) {
    return x / 255.0;
}

Color4f::Color4f(const Color4u& c) {
    r = u8tf(c.r);
    g = u8tf(c.g);
    b = u8tf(c.b);
    a = u8tf(c.a);
}

Color4u::Color4u(const Color4f& c) {
    r = ftu8(c.r);
    g = ftu8(c.g);
    b = ftu8(c.b);
    a = ftu8(c.a);
}
