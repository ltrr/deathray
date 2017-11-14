#include "util/random.h"

#include <random>

std::knuth_b generator{};
std::uniform_real_distribution<float> d{-1, 1};
std::uniform_real_distribution<float> u{0, 1};

float randf()
{
    return d(generator);
}

Point3 rand_on_unit_sphere()
{
    Point3 p;
    do {
        p = Point3(d(generator), d(generator), d(generator));
    } while(len2(p) >= 1);
    return p;
}


std::array<float, 2> rand_on_s1()
{
    float rh = sqrt(u(generator));
    float theta = 2 * PI * u(generator);
    return std::array<float, 2> { rh*cosf(theta), rh*sinf(theta) };
}
