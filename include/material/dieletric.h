#ifndef DEATHRAY_DIELETRIC_H_
#define DEATHRAY_DIELETRIC_H_

#include "material/material.h"


class Dieletric : public Material
{
private:
    float refract_index_;

public:
    Dieletric()
        : refract_index_(1) {}

    Dieletric(float ref_ind)
        : refract_index_(ref_ind) {}

    bool scatter(const Ray& in, const Hit& hit, Vec3& attenuation,
                 Ray& scattered);
};

#endif // DEATHRAY_DIELETRIC_H_
