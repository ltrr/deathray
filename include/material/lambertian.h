#ifndef DEATHRAY_MATERIAL_LAMBERTIAN_H_
#define DEATHRAY_MATERIAL_LAMBERTIAN_H_

#include "material/raytracematerial.h"


class Lambertian : public RaytraceMaterial
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

    bool scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const;

    Color3f albedo(const Hit& hit) const { return albedo_; }
    Color3f emission(const Hit& hit) const{ return emission_; }
};

#endif // DEATHRAY_MATERIAL_LAMBERTIAN_H_
