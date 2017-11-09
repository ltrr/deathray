#include "surface/sphere.h"
#include "util/math.h"
#include "util/transform.h"


Sphere::Sphere(const Transform& worldToUnit, const MaterialPtr& mat)
    : worldToUnit_(worldToUnit), material_(mat)
{
    using std::get;

    const Mat44& invM = worldToUnit.inv_matrix();
    Mat44 R = invM * Mat44(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,-1) * transpose(invM);

    auto bx = quadratic(R(3,3), -R(0,3), R(0,0));
    auto by = quadratic(R(3,3), -R(1,3), R(1,1));
    auto bz = quadratic(R(3,3), -R(2,3), R(2,2));

    Point3 p0 { get<1>(bx), get<1>(by), get<1>(bz) };
    Point3 p1 { get<2>(bx), get<2>(by), get<2>(bz) };

    this->bbox = BBox(p0, p1);
}


bool Sphere::hit(const Ray &ray, Hit& hit, float& error) const
{
    Point3 unit_origin = worldToUnit_.applyP(ray.origin());
    Vec3 unit_dir = worldToUnit_.applyV(ray.dir());
    float a = len2(unit_dir);
    float b = dot(unit_origin, unit_dir);
    float c = len2(unit_origin) - 1;
    float delta = (b*b - a* c);       // disc / 4

    if (delta >= 0) {
        float d = sqrt(delta);
        float root1 = -(d + b) / a;
        if (ray.over(root1)) {
            hit.t = root1;
            hit.point = ray.at(root1);
            hit.normal = unit(worldToUnit_.applyInvN(
                unit_origin + root1 * unit_dir));
            hit.material = this->material_;

            Vec3 diff = hit.point;
            hit.u = 10 * atan2(diff.y(), diff.x()) / TWO_PI;
            hit.v = 10 * acos(diff.z()) / PI;

            error = root1 * 1e-4f;
            return true;
        }
        float root2 = (d - b) / a;
        if (ray.over(root2)) {
            hit.t = root2;
            hit.point = ray.at(root2);
            hit.normal = unit(worldToUnit_.applyInvN(
                unit_origin + root2 * unit_dir));
            hit.material = this->material_;

            Vec3 diff = hit.point;
            hit.u = 10 * atan2(diff.y(), diff.x()) / TWO_PI;
            hit.v = 10 * acos(diff.z()) / PI;

            error = root2 * 1e-4f;
            return true;
        }
    }
    return false;
}


SurfacePtr Sphere::fromDescription(const SurfaceDescription *surf,
    const Transform& sphereToWorld)
{
    const SphereDescription *sp = dynamic_cast<const SphereDescription *>(surf);

    float inv_radius = 1 / sp->radius;

    Transform worldToUnit =
        Transform::scale({inv_radius, inv_radius, inv_radius})
        * Transform::translate(-sp->center)
        * inv(sphereToWorld);

    return SurfacePtr(new Sphere(worldToUnit, sp->material));
}
