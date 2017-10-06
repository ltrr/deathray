#include "shader/toonshader.h"


Vec3 ToonShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit, shit;
    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), hit)) {
        Color3f color(0,0,0);
        float cos_ = fabs(dot(hit.normal, ray.dir()));
        if (cos_ < 0.2)
            return color;

        for (auto light : scene->lights()) {
            Vec3 pointToLight = light->directionFrom(hit.point);
            if (scene->hit(
                Ray(hit.point, pointToLight),
                100*EPS, std::numeric_limits<float>::max(), shit)) {
                continue;
            }
            Vec3 subcol = light->radianceAt(hit.point) *
                hit.material->toon(hit.normal, pointToLight);
            color = max(color, subcol);
        }
        return color;
    }
    else {
        return scene->background()->colorAt(ray);
    }
}
