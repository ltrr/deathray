#include "material/metal.h"

#include "surface/surface.h"
#include "util/random.h"
#include "util/ray.h"


bool Metal::scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const
{
    Vec3 ref = reflect(in, hit.normal);
    scattered = ref + fuzz_ * rand_on_unit_sphere();
    return (dot(scattered, hit.normal) > 0);
}
