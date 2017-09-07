#ifndef DEATHRAY_SCENE_H_
#define DEATHRAY_SCENE_H_

#include <limits>
#include <memory>
#include <vector>
#include "background/background.h"
#include "light/light.h"
#include "surface/surface.h"


class Scene
{
private:
    std::vector<SurfacePtr> surfaces_;
    std::vector<LightPtr> lights_;
    BackgroundPtr bg_;

public:
    Scene() {}

    Scene(BackgroundPtr bg)
        : bg_(bg) {}

    void addSurface(const SurfacePtr& surface)
    {
        surfaces_.push_back(surface);
    }

    void addLight(const LightPtr& light)
    {
        lights_.push_back(light);
    }

    bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
    {
        float lower_t = std::numeric_limits<float>::max();
        Hit temp_hit;

        for (auto obj : surfaces_) {
            if (obj->hit(ray, t_min, t_max, temp_hit)) {
                if (temp_hit.t < lower_t) {
                    lower_t = temp_hit.t;
                    hit = temp_hit;
                }
            }
        }
        return (lower_t != std::numeric_limits<float>::max());
    }


    inline const std::vector<LightPtr>& lights() const { return lights_; }
    inline const std::vector<SurfacePtr>& surfaces() const { return surfaces_; }

    inline BackgroundPtr background() const { return bg_; }
    inline BackgroundPtr& background() { return bg_; }
};


typedef std::shared_ptr<Scene> ScenePtr;

#endif // SCENE_DEATHRAY_H_
