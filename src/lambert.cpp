#include "lambert.h"

#include <random>
#include "object.h"


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


bool Lambert::scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                      Ray& scattered)
{
    attenuation = albedo;
    scattered = Ray(hit.point, hit.normal + rand_unitsphere());
    return true;
}
