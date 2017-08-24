#ifndef DEATHRAY_RAYTRACER_H_
#define DEATHRAY_RAYTRACER_H_

#include "rendermethod.h"


class RayTracer : public RenderMethod
{
private:
    int maxdepth_;

    Vec3 colorat_rec(const ScenePtr& scene, const Ray& ray, int depth);

public:
    RayTracer() :
        maxdepth_(40) {}

    RayTracer(int maxdepth_) :
        maxdepth_(maxdepth_) {}

    Vec3 colorat(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_RAYTRACER_H_
