#ifndef DEATHRAY_RENDERMETHOD_H_
#define DEATHRAY_RENDERMETHOD_H_

#include <memory>
#include "scene.h"
#include "ray.h"


class RenderMethod
{
public:
    virtual Vec3 colorat(const ScenePtr& scene, const Ray& ray) = 0;
};


typedef std::shared_ptr<RenderMethod> RenderMethodPtr;

#endif // DEATHRAY_RENDERMETHOD_H_
