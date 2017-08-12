#ifndef DEATHRAY_SCENE_H_
#define DEATHRAY_SCENE_H_

#include <vector>
#include <memory>
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

    bool hit(const Ray& ray)
    {
        for (auto obj : objects) {
            if (obj->hit(ray)) return true;
        }
        return false;
    }
};


typedef std::shared_ptr<Scene> ScenePtr;

#endif // SCENE_DEATHRAY_H_
