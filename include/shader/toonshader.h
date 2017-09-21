#ifndef DEATHRAY_TOONSHADER_H_
#define DEATHRAY_TOONSHADER_H_

#include "shader/shader.h"


class ToonShader : public Shader
{
public:
    Vec3 colorAt(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_TOONSHADER_H_
