#ifndef DEATHRAY_MATERIAL_TOON_H_
#define DEATHRAY_MATERIAL_TOON_H_

#include <vector>
#include "material/material.h"


class ToonMaterial : public Material
{
private:
    std::vector<Color3f> colors_;
    std::vector<float> stops_;

public:
    ToonMaterial()
        : colors_ {Color3f {0,0,0}}, stops_ {0.0, 1.0} {}

    ToonMaterial(const std::vector<Color3f>& colors,
         const std::vector<float>& stops)
         : colors_(colors), stops_(stops) { }

    Vec3 toon(const Vec3& n, const Vec3& l)
    {
        float t = (1+dot(n, l))/2;
        int i;
        for (i = 0; i < stops_.size() && stops_[i] > t; i++);
        return colors_[i];
    }
};


#endif // DEATHRAY_MATERIAL_TOON_H_
