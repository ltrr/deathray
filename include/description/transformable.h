#ifndef DEATHRAY_DESCRIPTION_TRANSFORMABLE_H_
#define DEATHRAY_DESCRIPTION_TRANSFORMABLE_H_


#include <memory>
#include <vector>
#include "util/transform.h"
#include "description/visitor.h"


class TransformableDescription
{
public:
    virtual void visit(SceneDescriptionVisitor *) = 0;
};


typedef std::shared_ptr<TransformableDescription> TransformableDescriptionPtr;


class TransformDescription : public TransformableDescription
{
public:
    Transform tr;
    std::vector<TransformableDescriptionPtr> elements;

    TransformDescription(const Transform& tr)
        : tr(tr) { }

    void visit(SceneDescriptionVisitor *);
};

#endif // DEATHRAY_DESCRIPTION_TRANSFORMABLE_H_
