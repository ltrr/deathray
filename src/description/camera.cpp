#include "description/camera.h"

#include "description/scene.h"

void CameraDescription::visit(SceneDescriptionVisitor *visitor)
{
    visitor->onCamera(this);
}
