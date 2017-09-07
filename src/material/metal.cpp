#include "material/metal.h"

#include "surface/surface.h"
#include "util/random.h"
#include "util/ray.h"


bool Metal::scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                    Ray& scattered)
{
    Vec3 ref = reflect(in.dir(), hit.normal);
    scattered = Ray(hit.point, ref + fuzz_*rand_on_unit_sphere());
    attenuation = albedo_;
    return (dot(scattered.dir(), hit.normal) > 0);
}
