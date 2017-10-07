#ifndef DEATHRAY_BACKGROUND_H_
#define DEATHRAY_BACKGROUND_H_

#include <memory>
#include "util/color.h"
#include "util/ray.h"


class Background
{
public:
    virtual ~Background() { }

    virtual Color3f colorAt(const Ray& dir) = 0;
};


typedef std::shared_ptr<Background> BackgroundPtr;

#endif // DEATHRAY_BACKGROUND_H_
