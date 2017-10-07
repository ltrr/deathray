#ifndef DEATHRAY_MATERIAL_RAYTRACEMATERIAL_H_
#define DEATHRAY_MATERIAL_RAYTRACEMATERIAL_H_

#include "material/material.h"
#include "util/hit.h"
#include "util/color.h"


class RaytraceMaterial : public Material
{
public:
    virtual bool scatter(const Vec3& in, const Hit& hit,
        Vec3& scattered) const = 0;

    virtual Color3f albedo(const Hit& hit) const
    {
        return {1, 1, 1};
    }

    virtual Color3f emission(const Hit& hit) const
    {
        return {0, 0, 0};
    }
};

#endif // DEATHRAY_MATERIAL_RAYTRACEMATERIAL_H_
