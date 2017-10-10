#ifndef DEATHRAY_MATERIAL_LAMBERTIAN_H_
#define DEATHRAY_MATERIAL_LAMBERTIAN_H_

#include "material/raytracematerial.h"


class Lambertian : public RaytraceMaterial
{
public:
    Lambertian()
        : RaytraceMaterial() { }

    Lambertian(const TexturePtr& albedo)
        : RaytraceMaterial(albedo) { }

    Lambertian(const TexturePtr& albedo, const TexturePtr& emission)
        : RaytraceMaterial(albedo, emission) { }

    bool scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const;
};

#endif // DEATHRAY_MATERIAL_LAMBERTIAN_H_
