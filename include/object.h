#ifndef DEATHRAY_OBJECT_H_
#define DEATHRAY_OBJECT_H_

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


class Object
{
public:
    virtual bool hit(const Ray &ray, float t_min,
                     float t_max, Hit& hit) const = 0;
};


typedef std::shared_ptr<Object> ObjectPtr;

#endif // DEATHRAY_OBJECT_H_
