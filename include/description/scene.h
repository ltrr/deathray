#ifndef DEATHRAY_DESCRIPTION_SCENE_H_
#define DEATHRAY_DESCRIPTION_SCENE_H_

class SceneDescriptionVisitor;
class SceneDescription;

#include "util/color.h"
#include "background/background.h"
#include "util/outputconfig.h"
#include "scene/viewport.h"
#include "shader/shader.h"
#include "description/transformable.h"


class SceneDescription
{
private:
    std::vector<TransformableDescriptionPtr> transformables_;

public:
    ViewportPtr viewport;
    OutputConfigPtr outputConfig;
    BackgroundPtr background;
    ShaderPtr shader;
    Color3f ambientLight;
    int sample_count;

    void addTransformable(const TransformableDescriptionPtr&);
    void visit(SceneDescriptionVisitor *) const;
};


typedef std::shared_ptr<SceneDescription> SceneDescriptionPtr;

#endif // DEATHRAY_DESCRIPTION_SCENE_H_
