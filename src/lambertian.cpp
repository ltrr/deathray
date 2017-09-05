#include "lambertian.h"

#include "surface.h"
#include "random.h"


bool Lambertian::scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                      Ray& scattered)
{
    attenuation = albedo_;
    scattered = Ray(hit.point, hit.normal + rand_on_unit_sphere());
    return true;
}
