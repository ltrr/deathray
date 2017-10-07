#ifndef DEATHRAY_RAY_H_
#define DEATHRAY_RAY_H_

#include "util/math.h"
#include "util/vector.h"

class Ray
{
private:
    Point3 origin_;
    Vec3 dir_;
    float mint_, maxt_;

public:
    Ray()
        : origin_(), dir_(1,0,0), mint_(0), maxt_(FLOAT_INF) {}

    Ray(Point3 origin, Vec3 dir)
        : origin_(origin), dir_(unit(dir)), mint_(0), maxt_(FLOAT_INF) {}

    Ray(Point3 origin, Vec3 dir, float mint)
        : origin_(origin), dir_(unit(dir)), mint_(mint), maxt_(FLOAT_INF) {}

    Ray(Point3 origin, Vec3 dir, float mint, float maxt)
        : origin_(origin), dir_(unit(dir)), mint_(mint), maxt_(maxt) {}

    inline Vec3 dir() const { return dir_; }
    inline Point3 origin() const { return origin_; }
    inline float mint() const { return mint_; }
    inline float maxt() const { return maxt_; }

    inline bool over(float t) const { return (mint_ < t && t <= maxt_); }
    inline Point3 at(float t) const { return origin_ + t * dir_; }
};

#endif // DEATHRAY_RAY_HPP_
