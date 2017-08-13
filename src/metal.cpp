#include "metal.h"

#include "random.h"
#include "ray.h"
#include "object.h"

bool Metal::scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                    Ray& scattered)
{
    Vec3 ref = reflect(in.dir(), hit.normal);
    scattered = Ray(hit.point, ref + fuzz*rand_unitsphere());
    attenuation = albedo;
    return (dot(scattered.dir(), hit.normal) > 0);
}
