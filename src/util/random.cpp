#include "util/random.h"

#include <random>

std::knuth_b generator{};
std::uniform_real_distribution<float> d{-1, 1};

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
