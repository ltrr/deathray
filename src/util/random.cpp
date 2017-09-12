#include "util/random.h"

#include <random>

std::knuth_b e{};
std::uniform_real_distribution<float> d{-1, 1};

float randf()
{
    return d(e);
}

Point3 rand_on_unit_sphere()
{
    Point3 p;
    do {
        p = Point3(d(e), d(e), d(e));
    } while(len2(p) >= 1);
    return p;
}
