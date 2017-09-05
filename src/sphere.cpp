#include "sphere.h"


bool Sphere::hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
{
    Vec3 diff = ray.origin() - center_;
    // float a = 1; // ray direction is unitary
    float b = dot(diff, ray.dir());  // B/2
    float c = len2(diff) - radius_ * radius_;    // C
    float delta = (b*b - c);       // disc / 4

    if (delta >= 0) {
        float d = sqrt(delta);
        float root1 = -(d + b);
        if (t_min < root1 && root1 <= t_max) {
            hit.t = root1;
            hit.point = ray.at(root1);
            hit.normal = unit(hit.point - center_);
            hit.material = this->material_;
            return true;
        }
        float root2 = (d - b);
        if (t_min < root2 && root2 <= t_max) {
            hit.t = root2;
            hit.point = ray.at(root2);
            hit.normal = unit(hit.point - center_);
            hit.material = this->material_;
            return true;
        }
    }
    return false;
}
