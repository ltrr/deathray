#ifndef DEATHRAY_LIGHT_H_
#define DEATHRAY_LIGHT_H_

#include <memory>
#include "util/color.h"
#include "util/vector.h"
#include "util/ray.h"


class Light
{
public:
    virtual ~Light() { }
    virtual Color3f radianceAt(const Point3& p) const = 0;
    virtual Ray rayFrom(const Point3& p) const = 0;
};

typedef std::shared_ptr<Light> LightPtr;

#endif // DEATHRAY_LIGHT_H_
