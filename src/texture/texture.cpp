#include "texture/texture.h"

const TexturePtr BLACK_TEXTURE   = TexturePtr(new ConstTexture({0,0,0}));
const TexturePtr GRAY_TEXTURE    = TexturePtr(new ConstTexture({.5,.5,.5}));
const TexturePtr WHITE_TEXTURE   = TexturePtr(new ConstTexture({1,1,1}));
const TexturePtr RED_TEXTURE     = TexturePtr(new ConstTexture({1,0,0}));
const TexturePtr GREEN_TEXTURE   = TexturePtr(new ConstTexture({0,1,0}));
const TexturePtr BLUE_TEXTURE    = TexturePtr(new ConstTexture({0,0,1}));
const TexturePtr YELLOW_TEXTURE  = TexturePtr(new ConstTexture({1,1,0}));
const TexturePtr CYAN_TEXTURE    = TexturePtr(new ConstTexture({0,1,1}));
const TexturePtr MAGENTA_TEXTURE = TexturePtr(new ConstTexture({1,0,1}));
