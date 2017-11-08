#include "shader/raytracer.h"

#include "material/raytracematerial.h"
#include "scene/scene.h"
#include "util/ray.h"


Vec3 RayTracer::colorAt_rec(const ScenePtr& scene, const Ray& ray, int depth)
{
    if (depth > maxdepth_) {
        return Vec3(0, 0, 0);
    }

    Hit hit;
    float error;
    if (scene->hit(ray, hit, error)) {
        Vec3 attenuation;
        Vec3 scattered;

        auto rt_mat = std::dynamic_pointer_cast<RaytraceMaterial>(hit.material);
        if (!rt_mat) {
            std::cerr << "ERROR: Atempted to use unkown material"
                      << "as raytracer material" << std::endl;
            throw std::bad_cast();
        }

        if(rt_mat->scatter(ray.dir(), hit, scattered)) {
            Ray r(hit.point, scattered, error);
            return rt_mat->albedo(hit) * colorAt_rec(scene, r, depth+1)
                   + rt_mat->emission(hit);
        }
        else {
            return Vec3(0, 0, 0);
        }
    }
    else {
        return scene->background()->colorAt(ray);
    }
}


Vec3 RayTracer::colorAt(const ScenePtr& scene, const Ray& ray)
{
    Ray r(ray.origin(), 4*ray.dir()); return colorAt_rec(scene, r, 0);
    //return colorAt_rec(scene, ray, 0);
}
