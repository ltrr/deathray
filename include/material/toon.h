#ifndef DEATHRAY_TOON_H_
#define DEATHRAY_TOON_H_

#include <vector>
#include "material/material.h"


class Toon : public Material
{
private:
    std::vector<Color3f> colors_;
    std::vector<float> stops_;

public:
    Toon()
        : colors_ {Color3f {0,0,0}}, stops_ {0.0, 1.0} {}

    Toon(const std::vector<Color3f>& colors,
         const std::vector<float>& stops)
            : colors_(colors), stops_(stops) {

                std::cerr << "stops[0]=" << stops[0] << '\n';
            }

    Vec3 toon(const Vec3& n, const Vec3& l)
    {
        float t = (1+dot(n, l))/2;
        //return {cos_, cos_, cos_};

        int i;
        for (i = 0; i < stops_.size() && stops_[i] > t; i++);
        return colors_[i];
    }
};


#endif // DEATHRAY_TOON_H_
