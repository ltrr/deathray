#include "material/blinnphong.h"

#include "surface/surface.h"
#include "util/random.h"


bool BlinnPhong::scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                      Ray& scattered)
{
    attenuation = diffuse_;
    scattered = Ray(hit.point, hit.normal + rand_on_unit_sphere());
    return true;
}
