#include "shader/normalshader.h"


Vec3 NormalShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit;
    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), hit)) {
        return 0.5 * (hit.normal + Vec3(1,1,1));
    }
    else {
        return scene->background()->colorAt(ray);
    }
}
