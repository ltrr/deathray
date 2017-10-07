#ifndef DEATHRAY_MATERIAL_DIELETRIC_H_
#define DEATHRAY_MATERIAL_DIELETRIC_H_

#include "material/raytracematerial.h"


class Dieletric : public RaytraceMaterial
{
private:
    float refract_index_;

public:
    Dieletric()
        : refract_index_(1) {}

    Dieletric(float ref_ind)
        : refract_index_(ref_ind) {}

    bool scatter(const Vec3& in, const Hit& hit, Vec3& scattered) const;
};

#endif // DEATHRAY_MATERIAL_DIELETRIC_H_
