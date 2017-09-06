#ifndef DEATHRAY_LIGHT_H_
#define DEATHRAY_LIGHT_H_

#include <memory>
#include "vector.h"
#include "color.h"


class Light
{
public:
    virtual Color3f radianceAt(const Point3& p) = 0;
    virtual Vec3 directionFrom(const Point3& p) = 0;
};

typedef std::shared_ptr<Light> LightPtr;

#endif // DEATHRAY_LIGHT_H_
