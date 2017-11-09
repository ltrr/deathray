#include "surface/plane.h"


Plane::Plane()
    : Plane({0, 0, 0}, {0, 0, 1}, MaterialPtr()) { }


Plane::Plane(const Point3& p, const Vec3& n, MaterialPtr mat)
    : p_(p), n_(n), material_(mat)
{
    if (n[0] == 1 && n[1] == 0 && n[2] == 0) {
        Point3 q { p.x() + 1e4f, FLOAT_INF, FLOAT_INF };
        this->bbox = BBox(q, -q);
    }
    else if (n[0] == 0 && n[1] == 1 && n[2] == 0) {
        Point3 q { FLOAT_INF, p.y() + 1e4f, FLOAT_INF };
        this->bbox = BBox(q, -q);
    }
    else if (n[0] == 1 && n[1] == 0 && n[2] == 0) {
        Point3 q { FLOAT_INF, FLOAT_INF, p.z() + 1e4f };
        this->bbox = BBox(q, -q);
    }
    else {
        Point3 q { FLOAT_INF, FLOAT_INF, FLOAT_INF };
        this->bbox = BBox(q, -q);
    }
}


Plane::Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3, MaterialPtr mat)
    : Plane(p1, cross(p2 - p1, p3 - p1), mat) { }


bool Plane::hit(const Ray &ray, Hit& hit, float& error) const
{
    float dn = dot(ray.dir(), n_);
    if (dn == 0) // parallel
        return false;

    float t = dot(p_ - ray.origin(), n_) / dn;

    if (!ray.over(t))
        return false;

    hit.t = t;
    hit.point = ray.at(t);
    hit.normal = unit(dn > 0 ? -n_ : n_);
    hit.material = material_;
    error = t * 1e-3f;

    return true;
}


SurfacePtr Plane::fromDescription(const SurfaceDescription *surf,
    const Transform&)
{
    const PlaneDescription *plane =
        dynamic_cast<const PlaneDescription *>(surf);
    return SurfacePtr(new Plane(plane->point, plane->normal, plane->material));
}
