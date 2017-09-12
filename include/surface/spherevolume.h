#ifndef DEATHRAY_SPHEREVOLUME_H_
#define DEATHRAY_SPHEREVOLUME_H_

#include "material/material.h"
#include "surface/surface.h"
#include "util/ray.h"
#include "util/vector.h"
#include "util/random.h"

class SphereVolume : public Surface
{
private:
    Point3 center_;
    float radius_;
    MaterialPtr material_;
    float density;

public:
    SphereVolume()
        : center_(0,0,0), radius_(1.0), density(1) {}

    SphereVolume(Vec3 center, float radius, float density,
        const MaterialPtr& mat)
        : center_(center), radius_(radius), density(density), material_(mat) {}

    inline Point3 center() const { return center_; }
    inline float radius() const { return radius_; }

    bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const;
};

#endif // DEATHRAY_SPHEREVOLUME_H_
