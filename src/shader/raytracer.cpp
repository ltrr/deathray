#include "shader/raytracer.h"

#include <limits>
#include "scene/scene.h"
#include "util/ray.h"


Vec3 RayTracer::colorAt_rec(const ScenePtr& scene, const Ray& ray, int depth)
{
    if (depth > maxdepth_) {
        return Vec3(1, 0, 0);
    }

    Hit hit;
    if (scene->hit(ray, EPS, std::numeric_limits<float>::max(), hit)) {
        Vec3 attenuation;
        Ray scattered;

        if(hit.material->scatter(ray, hit, attenuation, scattered)) {
            //return .5*(scattered.dir() + Vec3(1,1,1));
            //if (depth < 1)
            return attenuation * colorAt_rec(scene, scattered, depth+1);
            //else return Vec3(0,0,1);
        }
        else {
            return Vec3(0, 1, 0);
        }
    }
    else {
        return scene->background()->colorAt(ray);
    }
}


Vec3 RayTracer::colorAt(const ScenePtr& scene, const Ray& ray)
{
    return colorAt_rec(scene, ray, 0);
}