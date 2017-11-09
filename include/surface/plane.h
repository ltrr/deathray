#ifndef DEATHRAY_SURFACE_PLANE_H_
#define DEATHRAY_SURFACE_PLANE_H_

#include "material/material.h"
#include "surface/surface.h"
#include "description/surface.h"

class Plane : public Surface
{
private:
    Point3 p_;
    Vec3 n_;
    MaterialPtr material_;

public:
    Plane();

    Plane(const Point3& p, const Vec3& n, MaterialPtr mat);

    Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3, MaterialPtr mat);

    bool hit(const Ray &ray, Hit& hit, float& error) const;

    static SurfacePtr fromDescription(const SurfaceDescription *,
        const Transform&);
};

#endif // DEATHRAY_SURFACE_PLANE_H_
