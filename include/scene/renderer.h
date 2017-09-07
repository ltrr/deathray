#ifndef DEATHRAY_RENDERER_H_
#define DEATHRAY_RENDERER_H_

#include <memory>
#include "scene/camera.h"
#include "scene/scene.h"
#include "scene/viewport.h"
#include "shader/shader.h"
#include "util/image.h"
#include "util/progressbar.h"


class ProgressBar;

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
    Image render(const RenderInfo& info, ProgressBar& progress);
};


typedef std::shared_ptr<Renderer> RendererPtr;

#endif // DEATHRAY_RENDERER_H_
