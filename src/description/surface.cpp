#include "description/surface.h"

#include "description/scene.h"

void SurfaceDescription::visit(SceneDescriptionVisitor *visitor)
{
    visitor->onSurface(this);
}
