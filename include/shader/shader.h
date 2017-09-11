#ifndef DEATHRAY_SHADER_H_
#define DEATHRAY_SHADER_H_

#include <memory>
#include "scene/scene.h"
#include "util/ray.h"

class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class Shader
{
public:
    virtual Vec3 colorAt(const ScenePtr& scene, const Ray& ray) = 0;
};


typedef std::shared_ptr<Shader> ShaderPtr;

#endif // DEATHRAY_SHADER_H_
