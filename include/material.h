#ifndef DEATHRAY_MATERIAL_H_
#define DEATHRAY_MATERIAL_H_

#include <memory>
#include "vector.h"


class Ray;
class Hit;


class Material
{
public:
    virtual bool scatter(const Ray& in, const Hit& hit,
                         Vec3& attenuation, Ray& scattered) = 0;
};


typedef std::shared_ptr<Material> MaterialPtr;

#endif // DEATHRAY_MATERIAL_H_
