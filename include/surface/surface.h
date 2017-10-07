#ifndef DEATHRAY_SURFACE_H_
#define DEATHRAY_SURFACE_H_

#include <memory>
#include "material/material.h"
#include "util/bbox.h"
#include "util/hit.h"
#include "util/ray.h"


class Surface
{
public:
    BBox bbox;

    Surface()
        : bbox() {}

    Surface(const BBox& bbox)
        : bbox(bbox) {}

    virtual ~Surface() { }

    virtual bool hit(const Ray &ray, Hit& hit, float& error) const = 0;
};


typedef std::shared_ptr<Surface> SurfacePtr;

#endif // DEATHRAY_SURFACE_H_
