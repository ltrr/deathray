#include "surface/sphere.h"
#include "util/math.h"


bool Sphere::hit(const Ray &ray, Hit& hit, float& error) const
{
    Vec3 diff = ray.origin() - center_;
    // float a = 1; // ray direction is unitary
    float b = dot(diff, ray.dir());  // B/2
    float c = len2(diff) - radius_ * radius_;    // C
    float delta = (b*b - c);       // disc / 4

    if (delta >= 0) {
        float d = sqrt(delta);
        float root1 = -(d + b);
        if (ray.over(root1)) {
            hit.t = root1;
            error = root1 * 1e-4f;
            hit.point = ray.at(root1);
            hit.normal = unit(hit.point - center_);
            hit.material = this->material_;
            return true;
        }
        float root2 = (d - b);
        if (ray.over(root2)) {
            hit.t = root2;
            error = root2 * 1e-4f;
            hit.point = ray.at(root2);
            hit.normal = unit(hit.point - center_);
            hit.material = this->material_;
            return true;
        }
    }
    return false;
}
