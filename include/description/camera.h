#ifndef DEATHRAY_DESCRIPTION_CAMERA_H_
#define DEATHRAY_DESCRIPTION_CAMERA_H_

#include "description/transformable.h"


enum class CameraKind { UNK, PERSPECTIVE, ORTOGONAL };

class CameraDescription : public TransformableDescription
{
public:
    void visit(SceneDescriptionVisitor *);

    virtual CameraKind getKind() const { return CameraKind::UNK; }
};


class PerspectiveCameraDescription : public CameraDescription
{
public:
    Point3 position;
    Point3 target;
    Vec3 up;

    float field_of_view;
    float aspect_ratio;

    CameraKind getKind() const { return CameraKind::PERSPECTIVE; }
};


typedef std::shared_ptr<CameraDescription> CameraDescriptionPtr;

#endif // DEATHRAY_DESCRIPTION_CAMERA_H_
