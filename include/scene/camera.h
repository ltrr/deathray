#ifndef DEATHRAY_CAMERA_H
#define DEATHRAY_CAMERA_H

#include <memory>
#include "util/ray.h"
#include "util/vector.h"


class Camera
{
public:
    virtual Ray windowToRay(const Vec3& v) const = 0;
};


class PerspectiveCamera : public Camera
{
private:
    Vec3 origin_, bottomleft_, horizontal_, vertical_;

public:
    PerspectiveCamera();

    PerspectiveCamera(const Point3& origin, const Point3& target,
        const Vec3& up, float fov, float aspect);

    Ray windowToRay(const Vec3& v) const;
};


typedef std::shared_ptr<Camera> CameraPtr;

#endif // DEATHRAY_CAMERA_H
