#include "description/visitor.h"

#include "description/surface.h"
#include "description/light.h"
#include "description/camera.h"


SceneDescriptionVisitor::~SceneDescriptionVisitor() { }

void SceneDescriptionVisitor::onSurface(const SurfaceDescription *) { }

void SceneDescriptionVisitor::onLight(const LightDescription *) { }

void SceneDescriptionVisitor::onCamera(const CameraDescription *) { }

void SceneDescriptionVisitor::onEnterTransform(const Transform&) { }

void SceneDescriptionVisitor::onExitTransform() { }
