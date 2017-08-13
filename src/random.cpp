#include "random.h"

#include <random>


Point3 rand_unitsphere()
{
    static std::default_random_engine e{};
    static std::uniform_real_distribution<float> d{-1, 1};
    Point3 p;
    do {
        p = Point3(d(e), d(e), d(e));
    } while(len2(p) >= 1);
    return p;
}
