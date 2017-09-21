#include "shader/blinnphongshader.h"


Vec3 BlinnPhongShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit, shit;
    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), hit)) {
        Color3f color(hit.material->ambient() * scene->ambient());
        for (auto light : scene->lights()) {
            Vec3 pointToLight = light->directionFrom(hit.point);

            if (scene->hit(
                Ray(hit.point, pointToLight),
                1000*EPS, std::numeric_limits<float>::max(), shit)) {
                continue;
            }

            float cos_nl = max(0.0f, dot(pointToLight, hit.normal));
            Vec3 half = unit(pointToLight - ray.dir());

            color += light->radianceAt(hit.point) * (
                hit.material->specular() * pow(dot(half, hit.normal), hit.material->shiness())
            + hit.material->diffuse() * cos_nl);
        }
        return color;
    }
    else {
        return scene->background()->colorAt(ray);
    }
}
