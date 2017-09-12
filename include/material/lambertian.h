#ifndef DEATHRAY_LAMBERTIAN_H_
#define DEATHRAY_LAMBERTIAN_H_

#include "material/material.h"


class Lambertian : public Material
{
private:
    Vec3 albedo_, emission_;

public:
    Lambertian()
        : albedo_(0, 0, 0) {}

    Lambertian(const Vec3& albedo)
        : albedo_(albedo) {}

    Lambertian(const Vec3& albedo, const Vec3& emission)
        : albedo_(albedo), emission_(emission) {}

    bool scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                 Ray& scattered);

    virtual Vec3 emission() { return emission_; }
};

#endif // DEATHRAY_LAMBERTIAN_H_
