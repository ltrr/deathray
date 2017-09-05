#ifndef DEATHRAY_SURFACE_H_
#define DEATHRAY_SURFACE_H_

#include <memory>
#include "ray.h"
#include "material.h"

struct Hit
{
    float t;
    Point3 point;
    Vec3 normal;
    MaterialPtr material;
};


class Surface
{
public:
    virtual bool hit(const Ray &ray, float t_min,
                     float t_max, Hit& hit) const = 0;
};


typedef std::shared_ptr<Surface> SurfacePtr;

#endif // DEATHRAY_SURFACE_H_
