#ifndef DEATHRAY_SCENE_H_
#define DEATHRAY_SCENE_H_

#include <vector>
#include <memory>
#include <limits>
#include "object.h"
#include "background.h"


class Scene
{
private:
    std::vector<ObjectPtr> objects;
    BackgroundPtr bg;

public:
    Scene() {}

    Scene(BackgroundPtr bg)
        : bg(bg) {}

    void addobject(const ObjectPtr& obj)
    {
        objects.push_back(obj);
    }

    bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
    {
        float lower_t = std::numeric_limits<float>::max();
        Hit temp_hit;

        for (auto obj : objects) {
            if (obj->hit(ray, t_min, t_max, temp_hit)) {
                if (temp_hit.t < lower_t) {
                    lower_t = temp_hit.t;
                    hit = temp_hit;
                }
            }
        }
        return (lower_t != std::numeric_limits<float>::max());
    }

    inline BackgroundPtr background() const { return bg; }
    inline BackgroundPtr& background() { return bg; }
};


typedef std::shared_ptr<Scene> ScenePtr;

#endif // SCENE_DEATHRAY_H_
