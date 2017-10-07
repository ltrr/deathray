#ifndef DEATHRAY_MATERIAL_METAL_H_
#define DEATHRAY_MATERIAL_METAL_H_

#include "material/raytracematerial.h"


class Metal : public RaytraceMaterial
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

    bool scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const;

    Vec3 albedo() const { return albedo_; }
    Vec3 emission() const { return emission_; }
};

#endif // DEATHRAY_MATERIAL_METAL_H_
