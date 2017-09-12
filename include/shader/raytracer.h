#ifndef DEATHRAY_RAYTRACER_H_
#define DEATHRAY_RAYTRACER_H_

#include "shader/shader.h"


class RayTracer : public Shader
{
private:
    int maxdepth_;

    Vec3 colorAt_rec(const ScenePtr& scene, const Ray& ray, int depth);

public:
    RayTracer() :
        maxdepth_(3) {}

    RayTracer(int maxdepth_) :
        maxdepth_(maxdepth_) {}

    Vec3 colorAt(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_RAYTRACER_H_
