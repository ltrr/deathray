#ifndef DEATHRAY_SPHERE_H_
#define DEATHRAY_SPHERE_H_

#include "vector.h"
#include "ray.h"
#include "object.h"

class Sphere : public Object
{
private:
    Point3 c_;
    float r_;

public:
    Sphere()
        : c_(0,0,0), r_(1.0) {}

    Sphere(Vec3 center, float radius)
        : c_(center), r_(radius) {}

    inline Point3 center() const { return c_; }
    inline float radius() const { return r_; }

    bool hit(const Ray &ray) const
    {
        Vec3 diff = ray.origin() - c_;
        float A = len2(ray.dir());
        float B = 2*dot(diff, ray.dir());
        float C = len2(c_) - r_ * r_;
        return (B*B - 4*A*C) >= 0;
    }
};

#endif // DEATHRAY_SPHERE_H_
