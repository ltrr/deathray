#include "surface/sphere.h"
#include "util/math.h"
#include "util/transform.h"


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
            hit.point = ray.at(root1);
            hit.normal = unit(hit.point - center_);
            hit.material = this->material_;

            Vec3 diff = hit.point - center_;
            hit.u = 10 * atan2(diff.y(), diff.x()) / TWO_PI;
            hit.v = 10 * acos(diff.z()) / PI;

            error = root1 * 1e-4f;
            return true;
        }
        float root2 = (d - b);
        if (ray.over(root2)) {
            hit.t = root2;
            hit.point = ray.at(root2);
            hit.normal = unit(hit.point - center_);
            hit.material = this->material_;

            Vec3 diff = hit.point - center_;
            hit.u = 10 * atan2(diff.y(), diff.x()) / TWO_PI;
            hit.v = 10 * acos(diff.z()) / PI;

            error = root2 * 1e-4f;
            return true;
        }
    }
    return false;
}


SurfacePtr Sphere::fromDescription(const SurfaceDescription *surf,
    const Transform&)
{
    const SphereDescription *sp = dynamic_cast<const SphereDescription *>(surf);
    return SurfacePtr(new Sphere(sp->center, sp->radius, sp->material));
}
