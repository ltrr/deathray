#include "description/transformable.h"

void TransformDescription::visit(SceneDescriptionVisitor *visitor)
{
    visitor->onEnterTransform(tr);
    for (auto& element : elements) {
        element->visit(visitor);
    }
    visitor->onExitTransform();
}
