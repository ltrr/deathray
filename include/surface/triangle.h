#ifndef DEATHRAY_TRIANGE_H_
#define DEATHRAY_TRIANGE_H_

#include "material/material.h"
#include "surface/surface.h"


class Triangle : public Surface
{
private:
    Point3 origin_;
    Vec3 u_, v_, n_;
    MaterialPtr material_;

public:
    Triangle()
        : origin_(0,0,0), u_(1,0,0), v_(0,1,0), n_(0,0,1),
          Surface({{0,0,0}, {1,1,1}}) {}

    Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3, MaterialPtr mat);

    Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& normal,
        MaterialPtr mat);

    bool hit(const Ray &ray, Hit& hit, float& error) const;
};

#endif // DEATHRAY_TRIANGE_H_
