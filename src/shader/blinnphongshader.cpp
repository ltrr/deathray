#include "shader/blinnphongshader.h"

#include <memory>
#include <typeinfo>
#include "material/blinnphong.h"

Vec3 BlinnPhongShader::colorAt(const ScenePtr& scene, const Ray& ray)
{
    float error;
    Hit hit, shit;
    if (scene->hit(ray, hit, error)) {

        auto bp_mat = std::dynamic_pointer_cast<BlinnPhongMaterial>(hit.material);
        if (!bp_mat) {
            std::cerr << "ERROR: Atempted to use unkown material"
                      << "as Blinn-Phong material" << std::endl;
            throw std::bad_cast();
        }

        Color3f color(bp_mat->ambient() * scene->ambient());
        for (auto light : scene->lights()) {
            Ray pointToLight = light->rayFrom(hit.point + 0.0001*hit.normal);
            if (scene->hit(pointToLight, shit, error)) {
                continue;
            }
            float diff = max(0.0f, dot(pointToLight.dir(), hit.normal));
            Vec3 half = unit(pointToLight.dir() - ray.dir());
            float spec = pow(dot(half, hit.normal), bp_mat->shininess());

            color += light->radianceAt(hit.point)
                * (bp_mat->specular() * spec + bp_mat->diffuse() * diff);
        }
        return color;
    }
    else {
        return scene->background()->colorAt(ray);
    }
}
