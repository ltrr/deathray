#ifndef DEATHRAY_POINTLIGHT_H_
#define DEATHRAY_POINTLIGHT_H_

#include "light.h"


class PointLight : public Light
{
private:
    Point3 position_;
    Color3f intensity_;

public:
    PointLight()
        : position_(0,0,0), intensity_(0,0,0) {}

    PointLight(const Point3& pos, const Point3& intensity)
        : position_(pos), intensity_(intensity) {}

    Color3f radianceAt(const Point3& p) {
        return intensity_ / len2(p - position_);
    }

    Vec3 directionFrom(const Point3& p) {
        return unit(position_ - p);
    }
};

#endif // DEATHRAY_POINTLIGHT_H_
