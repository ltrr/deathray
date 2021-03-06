#include "scene/scenebuilder.h"
#include "surface/triangle.h"
#include "surface/sphere.h"
#include "surface/plane.h"
#include "light/pointlight.h"
#include "light/spotlight.h"
#include "light/sun.h"


SceneBuilder::SceneBuilder()
    : scene(nullptr) { }


SceneBuilder::~SceneBuilder()
{
    if (scene != nullptr)
        delete scene;
}


void SceneBuilder::start(const SceneDescriptionPtr &description)
{
    scene = new Scene();
    scene->viewport() = description->viewport;
    scene->background() = description->background;
    scene->shader() = description->shader;
    scene->ambient() = description->ambientLight;
    scene->viewport() = description->viewport;
    scene->outputConfig() = description->outputConfig;
    scene->sampleCount() = description->sample_count;

    tr_stack.clear();
    tr_stack.push_back(Transform::eye());
}


void SceneBuilder::onSurface(const SurfaceDescription *surf)
{
    switch (surf->getKind()) {
        case SurfaceKind::TRIANGLE:
            scene->addSurface(Triangle::fromDescription(surf, tr_stack.back()));
            break;
        case SurfaceKind::SPHERE:
            scene->addSurface(Sphere::fromDescription(surf, tr_stack.back()));
            break;
        case SurfaceKind::PLANE:
            scene->addSurface(Plane::fromDescription(surf, tr_stack.back()));
            break;
        case SurfaceKind::MESH:
            auto surfs = Triangle::fromMeshDescription(surf, tr_stack.back());
            for (auto surf : surfs) scene->addSurface(surf);
            break;
    }
}


void SceneBuilder::onLight(const LightDescription *light)
{
    switch (light->getKind()) {
        case LightKind::POINT:
            scene->addLight(
                PointLight::fromDescription(light, tr_stack.back()));
            break;
        case LightKind::SPOT:
            scene->addLight(
                SpotLight::fromDescription(light, tr_stack.back()));
            break;
        case LightKind::DIRECTIONAL:
            scene->addLight(Sun::fromDescription(light, tr_stack.back()));
            break;
    }
}


void SceneBuilder::onCamera(const CameraDescription *cam)
{
    switch (cam->getKind()) {
        case CameraKind::PERSPECTIVE:
            scene->camera() = PerspectiveCamera::fromDescription(cam);
            break;
        case CameraKind::ORTHOGONAL:
            scene->camera() = OrthogonalCamera::fromDescription(cam);
            break;
    }
}


void SceneBuilder::onEnterTransform(const Transform& tr)
{
    Transform new_tr = tr_stack.back() * tr;
    tr_stack.push_back(new_tr);
}

void SceneBuilder::onExitTransform()
{
    tr_stack.pop_back();
}


ScenePtr SceneBuilder::finish()
{
    // scene.accelerate();
    ScenePtr scene_ptr(scene);
    scene = nullptr;
    return scene_ptr;
}
