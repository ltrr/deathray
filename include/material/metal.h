#ifndef DEATHRAY_METAL_H_
#define DEATHRAY_METAL_H_

#include "material/material.h"


class Metal : public Material
{
private:
    Vec3 albedo_, emission_;
    float fuzz_;

public:
    Metal()
        : albedo_(0, 0, 0), fuzz_(0) {}

    Metal(const Vec3& albedo, float fuzz)
        : albedo_(albedo), fuzz_(fuzz) {}

    Metal(const Vec3& albedo, float fuzz, const Vec3& emission)
        : albedo_(albedo), fuzz_(fuzz), emission_(emission) {}

    bool scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                 Ray& scattered);

    virtual Vec3 emission() { return emission_; }
};

#endif // DEATHRAY_METAL_H_
