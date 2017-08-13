#ifndef DEATHRAY_METAL_H_
#define DEATHRAY_METAL_H_

#include "material.h"


class Metal : public Material
{
private:
    Vec3 albedo;
    float fuzz;

public:
    Metal()
        : albedo(0, 0, 0), fuzz(0) {}

    Metal(const Vec3& albedo, float fuzz)
        : albedo(albedo), fuzz(fuzz) {}

    bool scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                 Ray& scattered);
};

#endif // DEATHRAY_METAL_H_
