#ifndef DEATHRAY_DEPTHSHADER_H_
#define DEATHRAY_DEPTHSHADER_H_

#include "shader.h"
#include "color.h"

class DepthShader : public Shader
{
private:
    float depth_;
    Color3f foreground_, background_;

public:
    DepthShader()
        : depth_(1.0f), foreground_(1,1,1), background_(0,0,0) {}

    DepthShader(float depth_)
        : depth_(depth_), foreground_(1,1,1), background_(0,0,0) {}

    DepthShader(float depth_, const Color3f& fg, const Color3f& bg)
        : depth_(depth_), foreground_(fg), background_(bg) {}

    Vec3 colorAt(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_DEPTHSHADER_H_
