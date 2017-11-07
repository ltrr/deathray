#include "description/scene.h"


void SceneDescription::addTransformable(const TransformableDescriptionPtr& tr)
{
    if (!tr) throw 1;
    this->transformables_.push_back(tr);
}


void SceneDescription::visit(SceneDescriptionVisitor *visitor) const
{
    for (auto transformable : this->transformables_)
    {
        transformable->visit(visitor);
    }
}
