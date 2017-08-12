#include "camera.h"



//// class PerspectiveCamera ////
PerspectiveCamera::PerspectiveCamera()
    : origin(0, 0, 0),
      bottomleft(-1, -1, 0),
      vertical(0, 2, 0),
      horizontal(2, 0, 0) {}


PerspectiveCamera::PerspectiveCamera(
    const Point3& origin,
    const Vec3& front,
    const Vec3& up,
    float fov,
    float aspect)
{
    Vec3 front_u  = unit(front);
    Vec3 up_u = unit(up - front_u * dot(front_u, up));
    Vec3 right_u = cross(front_u, up_u);

    float w = tan(fov/2);
    float h = w / aspect;

    this->origin = origin;
    this->horizontal = 2 * w * right_u;
    this->vertical   = 2 * h * up_u;
    this->bottomleft = front - h*up_u - w * right_u;
}


PerspectiveCamera PerspectiveCamera::lookat(
    const Point3& origin,
    const Point3& target,
    const Vec3& up,
    float fov,
    float aspect)
{
    return PerspectiveCamera(origin, target - origin, up, fov, aspect);
}


Ray PerspectiveCamera::windowtoray(const Vec3& uv) const
{
    Vec3 target = bottomleft + uv.x * horizontal + uv.y * vertical;
    return Ray(origin, target);
}
