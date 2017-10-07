#include "material/lambertian.h"

#include "surface/surface.h"
#include "util/random.h"


bool Lambertian::scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const
{
    scattered = hit.normal + rand_on_unit_sphere();
    return true;
}
