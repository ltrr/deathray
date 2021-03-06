#ifndef DEATHRAY_SPHERE_H_
#define DEATHRAY_SPHERE_H_

#include "material/material.h"
#include "surface/surface.h"
#include "description/surface.h"
#include "util/ray.h"
#include "util/transform.h"
#include "util/vector.h"


class Sphere : public Surface
{
private:

    Transform worldToUnit_;

    Point3 center_;
    float radius_;
    MaterialPtr material_;

public:
    Sphere()
        : center_(0,0,0), radius_(1.0), Surface({{-1,-1,-1}, {1,1,1}}) {}

    Sphere(Vec3 center, float r, const MaterialPtr& mat)
        : center_(center), radius_(r), material_(mat),
          Surface({center-Vec3(r, r, r), center+Vec3(r, r, r)}) {}

    Sphere(const Transform& worldToUnit, const MaterialPtr& mat);

    inline Point3 center() const { return center_; }
    inline float radius() const { return radius_; }

    bool hit(const Ray &ray, Hit& hit, float& error) const;

    static SurfacePtr fromDescription(const SurfaceDescription *,
        const Transform&);
};

#endif // DEATHRAY_SPHERE_H_
