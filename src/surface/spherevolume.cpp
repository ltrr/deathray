#include "surface/spherevolume.h"
#include "util/random.h"


//std::default_random_engine gen(1);
std::exponential_distribution<float> dist(1);

bool SphereVolume::hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
{

    auto param = std::exponential_distribution<float>::param_type(1/density);

    Vec3 diff = ray.origin() - center_;
    // float a = 1; // ray direction is unitary
    float b = dot(diff, ray.dir());  // B/2
    float c = len2(diff) - radius_ * radius_;    // C
    float delta = (b*b - c);       // disc / 4

    if (delta >= 0) {
        float d = sqrt(delta);
        float root1 = -(d + b);
        float root2 = (d - b);

        float hitpoint = dist(generator, param) + root1;
        if (hitpoint >= root2) return false;

        hit.t = hitpoint;
        hit.point = ray.at(hitpoint);
        hit.normal = unit(-ray.dir());
        hit.material = this->material_;
        return true;
    }
    return false;
}
