#ifndef DEATHRAY_CAMERA_H
#define DEATHRAY_CAMERA_H

#include <memory>
#include "description/camera.h"
#include "util/ray.h"
#include "util/vector.h"

class Camera
{
public:
    virtual ~Camera() { }

    virtual Ray windowToRay(const Vec3& v) const = 0;
};


typedef std::shared_ptr<Camera> CameraPtr;


class PerspectiveCamera : public Camera
{
private:
    Vec3 origin_, bottomleft_, horizontal_, vertical_;

public:
    PerspectiveCamera();

    PerspectiveCamera(const Point3& origin, const Point3& target,
        const Vec3& up, float fov, float aspect);

    Ray windowToRay(const Vec3& v) const;

    static CameraPtr fromDescription(const CameraDescription *cam);
};


class OrthogonalCamera : public Camera
{
private:
    Vec3 direction_, bottomleft_, horizontal_, vertical_;

public:
    OrthogonalCamera();

    OrthogonalCamera(const Point3& origin, const Point3& target,
        const Vec3& up, float width, float height);

    Ray windowToRay(const Vec3& v) const;

    static CameraPtr fromDescription(const CameraDescription *cam);
};


#endif // DEATHRAY_CAMERA_H
