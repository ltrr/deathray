#ifndef DEATHRAY_TRIANGE_H_
#define DEATHRAY_TRIANGE_H_

#include "object.h"
#include "material.h"


class Triangle : public Object
{
private:
    Point3 origin;
    Vec3 u, v, n;
    MaterialPtr material;

public:
    Triangle() :
        origin(0,0,0), u(1,0,0), v(0,1,0), n(0,0,1) {}

    Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3, MaterialPtr mat);

    Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& normal,
        MaterialPtr mat);

    bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const;
};

#endif // DEATHRAY_TRIANGE_H_
