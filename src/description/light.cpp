#include "description/light.h"

#include "description/scene.h"

void LightDescription::visit(SceneDescriptionVisitor *visitor)
{
    visitor->onLight(this);
}
