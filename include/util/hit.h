#ifndef DEATHRAY_UTIL_HIT_H_
#define DEATHRAY_UTIL_HIT_H_

#include "util/vector.h"
#include "material/material.h"


struct Hit
{
    float t;
    Point3 point;
    Vec3 normal;
    MaterialPtr material;
};


#endif
