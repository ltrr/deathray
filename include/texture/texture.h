#ifndef DEATHRAY_TEXTURE_TEXTURE_H_
#define DEATHRAY_TEXTURE_TEXTURE_H_

#include <memory>
#include "util/color.h"
#include "util/hit.h"

class Texture
{
public:
    virtual ~Texture() { }

    virtual Color3f sample(const Hit& hit) const = 0;
};


class ConstTexture : public Texture
{
private:
    Color3f color_;

public:
    ConstTexture()
        : color_() { }

    ConstTexture(const Color3f& color)
        : color_(color) { }

    Color3f sample(const Hit& hit) const
    {
        return color_;
    }
};

typedef std::shared_ptr<Texture> TexturePtr;

extern const TexturePtr BLACK_TEXTURE;
extern const TexturePtr GRAY_TEXTURE;
extern const TexturePtr WHITE_TEXTURE;
extern const TexturePtr RED_TEXTURE;
extern const TexturePtr GREEN_TEXTURE;
extern const TexturePtr BLUE_TEXTURE;
extern const TexturePtr CYAN_TEXTURE;
extern const TexturePtr YELLOW_TEXTURE;
extern const TexturePtr MAGENTA_TEXTURE;

#endif
