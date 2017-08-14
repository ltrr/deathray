#ifndef DEATHRAY_BACKGROUND_H_
#define DEATHRAY_BACKGROUND_H_

#include <memory>
#include "ray.h"
#include "color.h"


class Background
{
public:
    virtual Color3f colorat(const Ray& dir) = 0;
};


typedef std::shared_ptr<Background> BackgroundPtr;

#endif // DEATHRAY_BACKGROUND_H_
