#include "rendernormal.h"


Vec3 RenderNormal::colorat(const ScenePtr& scene, const Ray& ray)
{
    Hit hit;
    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), hit)) {
        return 0.5 * (hit.normal + Vec3(1,1,1));
    }
    else {
        return scene->background()->colorat(ray);
    }
}
