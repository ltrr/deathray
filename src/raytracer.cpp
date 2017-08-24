#include "raytracer.h"

#include <limits>
#include "scene.h"
#include "ray.h"


Vec3 RayTracer::colorat_rec(const ScenePtr& scene, const Ray& ray, int depth)
{
    if (depth > maxdepth_) {
        return Vec3(0, 0, 0);
    }

    Hit hit;
    if (scene->hit(ray, 0, std::numeric_limits<float>::max(), hit)) {
        Vec3 attenuation;
        Ray scattered;

        if(hit.material->scatter(ray, hit, attenuation, scattered)) {
            return attenuation * colorat_rec(scene, scattered, depth+1);
        }
        else {
            return Vec3(0, 0, 0);
        }
    }
    else {
        return scene->background()->colorat(ray);
    }
}


Vec3 RayTracer::colorat(const ScenePtr& scene, const Ray& ray)
{
    return colorat_rec(scene, ray, 0);
}
