#include "depthshader.h"


Vec3 DepthShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit;
    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), hit)) {
        float s = (hit.t / depth_);
        return (1-s) * foreground_ + s * background_;
    }
    else {
        return background_;
    }
}
