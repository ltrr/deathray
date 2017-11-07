#ifndef DEATHRAY_SCENE_SCENEBUILDER_H_
#define DEATHRAY_SCENE_SCENEBUILDER_H_

#include "description/visitor.h"
#include "description/scene.h"
#include "description/surface.h"
#include "description/light.h"
#include "description/camera.h"
#include "scene/scene.h"

class SceneBuilder : public SceneDescriptionVisitor
{
private:
    Scene *scene;
    std::vector<Transform> tr_stack;

public:
    SceneBuilder();

    ~SceneBuilder();

    void start(const SceneDescriptionPtr&);

    void onSurface(const SurfaceDescription *);

    void onLight(const LightDescription *);

    void onCamera(const CameraDescription *);

    void onEnterTransform(const Transform&);

    void onExitTransform();

    ScenePtr finish();
};


#endif // DEATHRAY_SCENE_SCENEBUILDER_H_
