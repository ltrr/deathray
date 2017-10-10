#ifndef DEATHRAY_MATERIAL_RAYTRACEMATERIAL_H_
#define DEATHRAY_MATERIAL_RAYTRACEMATERIAL_H_

#include "material/material.h"
#include "texture/texture.h"
#include "util/hit.h"
#include "util/color.h"


class RaytraceMaterial : public Material
{
protected:
    TexturePtr albedo_tex_;
    TexturePtr emission_tex_;

public:
    RaytraceMaterial(
        const TexturePtr& albedo=WHITE_TEXTURE,
        const TexturePtr& emission=BLACK_TEXTURE)
        : albedo_tex_(albedo),
          emission_tex_(emission) { }

    virtual Color3f albedo(const Hit& hit) const
    {
        return albedo_tex_->sample(hit);
    }

    virtual Color3f emission(const Hit& hit) const
    {
        return emission_tex_->sample(hit);
    }

    virtual bool scatter(const Vec3& in, const Hit& hit,
        Vec3& scattered) const = 0;
};

#endif // DEATHRAY_MATERIAL_RAYTRACEMATERIAL_H_
