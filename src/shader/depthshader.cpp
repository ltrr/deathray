#include "shader/depthshader.h"
#include "scene/scene.h"


Vec3 DepthShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit;
    float error;
    if (scene->hit(ray, hit, error)) {
        float s = (hit.t / depth_);
        return (1-s) * foreground_ + s * background_;
    }
    else {
        return background_;
    }
}
