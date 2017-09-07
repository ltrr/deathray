#ifndef DEATHRAY_METAL_H_
#define DEATHRAY_METAL_H_

#include "material/material.h"


class Metal : public Material
{
private:
    Vec3 albedo_;
    float fuzz_;

public:
    Metal()
        : albedo_(0, 0, 0), fuzz_(0) {}

    Metal(const Vec3& albedo, float fuzz)
        : albedo_(albedo), fuzz_(fuzz) {}

    bool scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                 Ray& scattered);
};

#endif // DEATHRAY_METAL_H_
