#include "lambert.h"

#include "object.h"
#include "random.h"


bool Lambert::scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                      Ray& scattered)
{
    attenuation = albedo;
    scattered = Ray(hit.point, hit.normal + rand_unitsphere());
    return true;
}
