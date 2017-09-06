#ifndef DEATHRAY_MATERIAL_H_
#define DEATHRAY_MATERIAL_H_

#include <memory>
#include "vector.h"


class Ray;
class Hit;


class Material
{
public:
    virtual Vec3 diffuse() { return Vec3(0,0,0); }
    virtual Vec3 specular() { return Vec3(0,0,0); }
    virtual Vec3 ambient() { return Vec3(0,0,0); }
    virtual float shiness() { return 0; }

    virtual bool scatter(const Ray& in, const Hit& hit,
                         Vec3& attenuation, Ray& scattered) {};
};


typedef std::shared_ptr<Material> MaterialPtr;

#endif // DEATHRAY_MATERIAL_H_
