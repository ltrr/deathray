#ifndef DEATHRAY_RENDERNORMAL_H_
#define DEATHRAY_RENDERNORMAL_H_

#include "rendermethod.h"


class RenderNormal : public RenderMethod
{
public:
    Vec3 colorat(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_RENDERNORMAL_H_
