#ifndef DEATHRAY_RENDERER_H_
#define DEATHRAY_RENDERER_H_

#include <memory>
#include "scene.h"
#include "camera.h"
#include "viewport.h"
#include "image.h"
#include "shader.h"


struct RenderInfo
{
    ScenePtr scene;
    CameraPtr camera;
    ViewportPtr viewport;
    ShaderPtr shader;
    int num_samples = 1;
};


class Renderer
{
public:
    Image render(const RenderInfo& info);
};


typedef std::shared_ptr<Renderer> RendererPtr;

#endif // DEATHRAY_RENDERER_H_
