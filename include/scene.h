#ifndef DEATHRAY_SCENE_H_
#define DEATHRAY_SCENE_H_

#include <vector>
#include <memory>
#include <limits>
#include "surface.h"
#include "background.h"


class Scene
{
private:
    std::vector<SurfacePtr> surfaces_;
    BackgroundPtr bg_;

public:
    Scene() {}

    Scene(BackgroundPtr bg)
        : bg_(bg) {}

    void addSurface(const SurfacePtr& obj)
    {
        surfaces_.push_back(obj);
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

    inline BackgroundPtr background() const { return bg_; }
    inline BackgroundPtr& background() { return bg_; }
};


typedef std::shared_ptr<Scene> ScenePtr;

#endif // SCENE_DEATHRAY_H_
