#ifndef DEATHRAY_MATERIAL_BLINNPHONG_H_
#define DEATHRAY_MATERIAL_BLINNPHONG_H_

#include "material/material.h"


class BlinnPhongMaterial : public Material
{
private:
    Vec3 diffuse_, specular_, ambient_;
    float shininess_;

public:
    BlinnPhongMaterial()
        : diffuse_(0,0,0), specular_(0,0,0), ambient_(0,0,0), shininess_(0) {}

    BlinnPhongMaterial(const Vec3& diffuse, const Vec3& specular,
        const Vec3& ambient, float shininess)
        : diffuse_(diffuse), specular_(specular), ambient_(ambient),
          shininess_(shininess) { }

    Vec3 diffuse() { return diffuse_; }
    Vec3 specular() { return specular_; }
    Vec3 ambient() { return ambient_; }
    float shininess() { return shininess_; }
};


#endif // DEATHRAY_MATERIAL_BLINNPHONG_H_
