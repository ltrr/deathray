#ifndef DEATHRAY_RENDERDEPTH_H_
#define DEATHRAY_RENDERDEPTH_H_

#include "rendermethod.h"
#include "color.h"

class RenderDepth : public RenderMethod
{
private:
    float depth_;
    Color3f foreground_, background_;

public:
    RenderDepth()
        : depth_(1.0f), foreground_(1,1,1), background_(0,0,0) {}

    RenderDepth(float depth_)
        : depth_(depth_), foreground_(1,1,1), background_(0,0,0) {}

    RenderDepth(float depth_, const Color3f& fg, const Color3f& bg)
        : depth_(depth_), foreground_(fg), background_(bg) {}

    Vec3 colorat(const ScenePtr& scene, const Ray& ray);
};

#endif // DEATHRAY_RENDERDEPTH_H_
