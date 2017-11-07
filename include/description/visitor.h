#ifndef DEATHRAY_DESCRIPTION_VISITOR_H_
#define DEATHRAY_DESCRIPTION_VISITOR_H_

#include <memory>

class SurfaceDescription;
class LightDescription;
class CameraDescription;
class Transform;

class SceneDescriptionVisitor
{
public:
    virtual ~SceneDescriptionVisitor();

    virtual void onSurface(const SurfaceDescription *);

    virtual void onLight(const LightDescription *);

    virtual void onCamera(const CameraDescription *);

    virtual void onEnterTransform(const Transform&);

    virtual void onExitTransform();
};

#endif // DEATHRAY_DESCRIPTION_VISITOR_H_
