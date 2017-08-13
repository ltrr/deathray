#ifndef DEATHRAY_SCENE_H_
#define DEATHRAY_SCENE_H_

#include <vector>
#include <memory>
#include <limits>
#include "object.h"


class Scene
{
private:
    std::vector<ObjectPtr> objects;

public:
    Scene() {}

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
};


typedef std::shared_ptr<Scene> ScenePtr;

#endif // SCENE_DEATHRAY_H_
