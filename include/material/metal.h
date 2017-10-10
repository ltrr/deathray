#ifndef DEATHRAY_MATERIAL_METAL_H_
#define DEATHRAY_MATERIAL_METAL_H_

#include "material/raytracematerial.h"


class Metal : public RaytraceMaterial
{
private:
    float fuzz_;

public:
    Metal(const TexturePtr& albedo, float fuzz=0)
        : RaytraceMaterial(albedo), fuzz_(fuzz) { }

    Metal(const TexturePtr& albedo, float fuzz, const TexturePtr& emission)
        : RaytraceMaterial(albedo, emission), fuzz_(fuzz) { }

    bool scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const;
};

#endif // DEATHRAY_MATERIAL_METAL_H_
