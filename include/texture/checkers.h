#ifndef DEATHRAY_TEXTURE_CHECKERS_H_
#define DEATHRAY_TEXTURE_CHECKERS_H_

#include "texture/texture.h"


class CheckersTexture : public Texture
{
public:
    Color3f sample(const Hit& hit) const
    {
        float ub = hit.u - std::floor(hit.u);
        float vb = hit.v - std::floor(hit.v);
        if ((ub < .5) == (vb < .5)) {
            return {1, 1, 1};
        }
        else {
            return {0, 0, 0};
        }
    }
};


#endif // DEATHRAY_TEXTURE_CHECKERS_H_
