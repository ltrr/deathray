#ifndef DEATHRAY_BLINNPHONGSHADER_H_
#define DEATHRAY_BLINNPHONGSHADER_H_

#include "shader/shader.h"


class BlinnPhongShader : public Shader
{
public:
    Vec3 colorAt(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_BLINNPHONGSHADER_H_
