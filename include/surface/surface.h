#ifndef DEATHRAY_SURFACE_H_
#define DEATHRAY_SURFACE_H_

#include <memory>
#include "material/material.h"
#include "util/bbox.h"
#include "util/ray.h"


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
    BBox bbox;

    Surface()
        : bbox() {}

    Surface(const BBox& bbox)
        : bbox(bbox) {}

    virtual bool hit(const Ray &ray, float t_min,
                     float t_max, Hit& hit) const = 0;
};


typedef std::shared_ptr<Surface> SurfacePtr;

#endif // DEATHRAY_SURFACE_H_
