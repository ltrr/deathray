#ifndef DEATHRAY_DESCRIPTION_LIGHT_H_
#define DEATHRAY_DESCRIPTION_LIGHT_H_

#include "description/transformable.h"

#include "util/color.h"

enum class LightKind { UNK, POINT, SPOT, DIRECTIONAL };


class LightDescription : public TransformableDescription
{
public:
    void visit(SceneDescriptionVisitor *);

    virtual LightKind getKind() const { return LightKind::UNK; }
};


class PointLightDescription : public LightDescription
{
public:
    Point3 position;
    Color3f intensity;

    LightKind getKind() const { return LightKind::POINT; }
};


class SpotLightDescription : public LightDescription
{
public:
    Point3 position;
    Vec3 direction;
    Color3f intensity;
    float angle;
    float decay;

    LightKind getKind() const { return LightKind::SPOT; }
};


class DirectionalLightDescription : public LightDescription
{
public:
    Vec3 direction;
    Color3f intensity;

    LightKind getKind() const { return LightKind::DIRECTIONAL; }
};


typedef std::shared_ptr<LightDescription> LightDescriptionPtr;

#endif // DEATHRAY_DESCRIPTION_LIGHT_H_
