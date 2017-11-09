#ifndef DEATHRAY_SUN_H_
#define DEATHRAY_SUN_H_

#include "light.h"


class Sun : public Light
{
private:
    Vec3 direction_;
    Color3f intensity_;

public:
    Sun()
        : direction_(0,0,0), intensity_(0,0,0) {}

    Sun(const Vec3& dir, const Point3& intensity)
        : direction_(unit(dir)), intensity_(intensity) {}

    Color3f radianceAt(const Point3& p) const {
        return intensity_;
    }

    Ray rayFrom(const Point3& p) const {
        return Ray(p, direction_);
    }

    static LightPtr fromDescription(const LightDescription *desc,
        const Transform& tr)
    {
        const DirectionalLightDescription *dlight =
            dynamic_cast<const DirectionalLightDescription *>(desc);

        Point3 new_dir = tr.applyV(dlight->direction);

        return LightPtr(new Sun(new_dir, dlight->intensity));
    }
};

#endif // DEATHRAY_SUN_H_
