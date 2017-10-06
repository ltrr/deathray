#ifndef DEATHRAY_SPOTLIGHT_H_
#define DEATHRAY_SPOTLIGHT_H_

#include "light.h"


class SpotLight : public Light
{
private:
    Point3 position_;
    Vec3 direction_;
    Color3f intensity_;
    float angle_cos_;
    float decay_;

public:
    SpotLight() {}

    SpotLight(const Point3& pos, const Vec3& dir, const Point3& intensity,
        float angle, float decay)
        : position_(pos), direction_(unit(dir)), intensity_(intensity),
          angle_cos_(cos(angle)), decay_(decay) {}

    Color3f radianceAt(const Point3& p)
    {
        float proj = -dot(directionFrom(p), direction_);
        if(fabs(proj) < angle_cos_) {
            return Vec3();
        }
        //std::cerr << proj << '\n';
        return pow(proj, decay_) * intensity_ / len2(p - position_);
        //return proj * intensity_ / len2(p - position_);
    }

    Vec3 directionFrom(const Point3& p)
    {
        return unit(position_ - p);
    }
};

#endif // DEATHRAY_SPOTLIGHT_H_
