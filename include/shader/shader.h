#ifndef DEATHRAY_SHADER_H_
#define DEATHRAY_SHADER_H_

#include <memory>
#include "util/ray.h"

//#include "scene/scene.h"

class Scene;
typedef std::shared_ptr<Scene> ScenePtr;


class Shader
{
public:
    virtual ~Shader() { }

    virtual Vec3 colorAt(const ScenePtr& scene, const Ray& ray) = 0;
};


typedef std::shared_ptr<Shader> ShaderPtr;

#endif // DEATHRAY_SHADER_H_
