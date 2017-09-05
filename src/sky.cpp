#include "sky.h"


Sky::Sky()
    : zenith_(0,0,0), nadir_(0,0,0) {}


Sky::Sky(const Color3f& zenith_, const Color3f& nadir_)
    : zenith_(zenith_), nadir_(nadir_) {}


Color3f Sky::colorAt(const Ray& ray)
{
    float t = (1 + ray.dir().y) / 2;
    return t * zenith_ + (1-t) * nadir_;
}
