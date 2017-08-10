#ifndef DEATHRAY_COLOR_H_
#define DEATHRAY_COLOR_H_

#include <algorithm>
#include <cstdint>
#include "vector.h"
using std::min;
using std::max;

inline uint8_t ftu8(float x) {
    return max(0, min(255, int(256 * x)));
}

typedef Vec3 Color3f;

class Color3u {
public:
    uint8_t r, g, b;

    Color3u()
        : r(0), g(0), b(0) {}

    Color3u(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b) {}

    Color3u(const Vec3& v)
        : r(ftu8(v.x)), g(ftu8(v.y)), b(ftu8(v.z)) {}
};

#endif // DEATHRAY_COLOR_H_
