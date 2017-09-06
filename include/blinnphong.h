#ifndef DEATHRAY_BLINNPHONG_H_
#define DEATHRAY_BLINNPHONG_H_

#include "material.h"


class BlinnPhong : public Material
{
private:
    Vec3 diffuse_, specular_, ambient_;
    float shiness_;

public:
    BlinnPhong()
        : diffuse_(0,0,0), specular_(0,0,0), ambient_(0,0,0), shiness_(0) {}

        BlinnPhong(const Vec3& diffuse, const Vec3& specular,
            const Vec3& ambient, float shiness)
            : diffuse_(diffuse), specular_(specular), ambient_(ambient),
              shiness_(shiness) {}

    Vec3 diffuse() { return diffuse_; }
    Vec3 specular() { return specular_; }
    Vec3 ambient() { return ambient_; }
    float shiness() { return shiness_; }


};


#endif // DEATHRAY_BLINNPHONG_H_
