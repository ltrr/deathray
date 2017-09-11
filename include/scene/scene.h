#ifndef DEATHRAY_SCENE_H_
#define DEATHRAY_SCENE_H_

#include <limits>
#include <memory>
#include <vector>
#include "background/background.h"
#include "light/light.h"
#include "surface/surface.h"
#include "scene/camera.h"
#include "scene/viewport.h"
#include "shader/shader.h"
#include "util/outputconfig.h"


class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

class Scene
{
private:
    std::vector<SurfacePtr> surfaces_;
    std::vector<LightPtr> lights_;

    ViewportPtr viewport_;
    CameraPtr camera_;
    BackgroundPtr bg_;
    OutputConfigPtr config_;
    Color3f ambient_;
    ShaderPtr shader_;

    int sample_count_;

public:
    Scene()
        : sample_count_(1) {}

    void addSurface(const SurfacePtr& surface)
    {
        surfaces_.push_back(surface);
    }

    void addLight(const LightPtr& light)
    {
        lights_.push_back(light);
    }

    bool hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
    {
        float lower_t = std::numeric_limits<float>::max();
        Hit temp_hit;

        for (auto obj : surfaces_) {
            if (obj->hit(ray, t_min, t_max, temp_hit)) {
                if (temp_hit.t < lower_t) {
                    lower_t = temp_hit.t;
                    hit = temp_hit;
                }
            }
        }
        return (lower_t != std::numeric_limits<float>::max());
    }


    inline const std::vector<LightPtr>& lights() const { return lights_; }
    inline const std::vector<SurfacePtr>& surfaces() const { return surfaces_; }

    inline const BackgroundPtr& background() const { return bg_; }
    inline BackgroundPtr& background() { return bg_; }

    inline const Color3f& ambient() const { return ambient_; }
    inline Color3f& ambient() { return ambient_; }

    inline const ViewportPtr& viewport() const { return viewport_; }
    inline ViewportPtr& viewport() { return viewport_; }

    inline const CameraPtr& camera() const { return camera_; }
    inline CameraPtr& camera() { return camera_; }

    inline const ShaderPtr& shader() const { return shader_; }
    inline ShaderPtr& shader() { return shader_; }

    inline const OutputConfigPtr& outputConfig() const { return config_; }
    inline OutputConfigPtr& outputConfig() { return config_; }

    inline int sampleCount() const { return sample_count_; }
    inline int& sampleCount() { return sample_count_; }
};


typedef std::shared_ptr<Scene> ScenePtr;

#endif // SCENE_DEATHRAY_H_
