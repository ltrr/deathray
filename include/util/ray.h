#ifndef DEATHRAY_RAY_HPP_
#define DEATHRAY_RAY_HPP_

#include "vector.h"

class Ray
{
private:
    Point3 origin_;
    Vec3 dir_;

public:
    Ray() : origin_(), dir_(1,0,0) {}
    Ray(Point3 origin, Vec3 dir) : origin_(origin), dir_(unit(dir)) {}

    inline Vec3 dir() const { return dir_; }
    inline Point3 origin() const { return origin_; }
    inline Point3 at(float t) const {
        return origin_ + t * dir_;
    }
};

#endif // DEATHRAY_RAY_HPP_
