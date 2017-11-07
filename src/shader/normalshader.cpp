#include "shader/normalshader.h"
#include "scene/scene.h"


Vec3 NormalShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit;
    float error;
    if (scene->hit(ray, hit, error)) {
        return 0.5 * (hit.normal + Vec3(1,1,1));
    }
    else {
        return scene->background()->colorAt(ray);
    }
}
