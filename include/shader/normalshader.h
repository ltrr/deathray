#ifndef DEATHRAY_NORMALSHADER_H_
#define DEATHRAY_NORMALSHADER_H_

#include "shader/shader.h"


class NormalShader : public Shader
{
public:
    Vec3 colorAt(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_NORMALSHADER_H_
