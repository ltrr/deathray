#ifndef DEATHRAY_SPHERE_H_
#define DEATHRAY_SPHERE_H_

#include "vector.h"
#include "ray.h"
#include "surface.h"
#include "material.h"

class Sphere : public Surface
{
private:
    Point3 center_;
    float radius_;
    MaterialPtr material_;

public:
    Sphere()
        : center_(0,0,0), radius_(1.0) {}

    Sphere(Vec3 center, float radius, const MaterialPtr& mat)
        : center_(center), radius_(radius), material_(mat) {}

    inline Point3 center() const { return center_; }
    inline float radius() const { return radius_; }

    bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const;
};

#endif // DEATHRAY_SPHERE_H_
