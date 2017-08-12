#ifndef DEATHRAY_CAMERA_H
#define DEATHRAY_CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera
{
public:
    virtual Ray windowtoray(const Vec3& v) const = 0;
};

class PerspectiveCamera : public Camera
{
private:
    Vec3 origin, front, up, bottomleft, horizontal, vertical;

public:
    PerspectiveCamera();

    PerspectiveCamera(
        const Point3& origin,  // camera location
        const Vec3& front,     // front directed vector
        const Vec3& up,        // upwards directed vector
        float fov,             // field-of-view angle (horizontal)
        float aspect);          // screen width/height aspect

    static PerspectiveCamera lookat(
        const Point3& origin,  // camera location
        const Point3& target,  // targe
        const Vec3& up,        // upwards directed vector
        float fov,             // field-of-view angle (horizontal)
        float aspect);          // screen width/height aspect

    Ray windowtoray(const Vec3& v) const;
};

#endif // DEATHRAY_CAMERA_H
