#ifndef DEATHRAY_DEBUGSHADER_H_
#define DEATHRAY_DEBUGSHADER_H_

#include "scene/scene.h"
#include "shader/shader.h"
#include "util/bbox.h"


class BBoxShader : public Shader
{
public:
    Vec3 colorAt(const ScenePtr& scene, const Ray& ray)
    {
        for (const auto& surf : scene->surfaces())
        {
            if (surf->bbox.intersect(ray)) {
                return {1,0,0};
            }
        }
        return {0,0,1};
    }
};

#endif // DEATHRAY_DEBUGSHADER_H_
