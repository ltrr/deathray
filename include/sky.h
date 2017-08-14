#ifndef DEATHRAY_SKY_H_
#define DEATHRAY_SKY_H_

#include "background.h"
#include "color.h"


class Sky : public Background
{
private:
    Color3f zenith_, nadir_;

public:
    Sky();
    Sky(const Color3f& zenith_, const Color3f& nadir_);

    Color3f colorat(const Ray& ray);

    inline Color3f zenith() const { return zenith_; }
    inline Color3f nadir() const { return nadir_; }
};

#endif // DEATHRAY_SKY_H_
