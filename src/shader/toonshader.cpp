#include "shader/toonshader.h"
#include "material/toon.h"
#include "scene/scene.h"


Vec3 ToonShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Hit hit, shit;
    float error;
    if (scene->hit(ray, hit, error)) {
        Color3f color(0,0,0);
        float cos_ = fabs(dot(hit.normal, ray.dir()));
        if (cos_ < 0.2)
            return color;

        auto toon_mat = std::dynamic_pointer_cast<ToonMaterial>(hit.material);
        if (!toon_mat) {
            std::cerr << "ERROR: Atempted to use unkown material"
                      << "as toon material" << std::endl;
            throw std::bad_cast();
        }

        for (auto light : scene->lights()) {
            Ray pointToLight = light->rayFrom(hit.point + 1e-4f * unit(hit.normal));
            if (scene->hit(pointToLight, shit, error)) {
                continue;
            }
            Vec3 subcol = light->radianceAt(hit.point) *
                toon_mat->toon(hit.normal, pointToLight.dir());
            color = max(color, subcol);
        }
        return color;
    }
    else {
        return scene->background()->colorAt(ray);
    }
}
