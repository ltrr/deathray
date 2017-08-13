#ifndef DEATHRAY_LAMBERT_H_
#define DEATHRAY_LAMBERT_H_

#include "material.h"

class Lambert : public Material
{
private:
    Vec3 albedo;

public:
    Lambert()
        : albedo(0, 0, 0) {}

    Lambert(const Vec3& albedo)
        : albedo(albedo) {}

    bool scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                 Ray& scattered);
};

#endif // DEATHRAY_LAMBERT_H_
