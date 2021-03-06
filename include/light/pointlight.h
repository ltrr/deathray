#ifndef DEATHRAY_POINTLIGHT_H_
#define DEATHRAY_POINTLIGHT_H_

#include "light/light.h"
#include "description/light.h"


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

    Color3f radianceAt(const Point3& p) const
    {
        return intensity_ / len2(p - position_);
    }

    Ray rayFrom(const Point3& p) const
    {
        Vec3 delta = position_ - p;
        float delta_len = len(delta);
        return Ray(p, delta / delta_len, 0.f, delta_len);
    }

    static LightPtr fromDescription(const LightDescription *desc,
        const Transform& tr)
    {
        const PointLightDescription *plight =
            dynamic_cast<const PointLightDescription *>(desc);

        Point3 new_pos = tr.applyP(plight->position);

        return LightPtr(new PointLight(new_pos, plight->intensity));
    }
};

#endif // DEATHRAY_POINTLIGHT_H_
