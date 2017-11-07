#include "scene/camera.h"


PerspectiveCamera::PerspectiveCamera()
    : origin_(0, 0, 0),
      bottomleft_(-1, -1, 0),
      vertical_(0, 2, 0),
      horizontal_(2, 0, 0) {}


PerspectiveCamera::PerspectiveCamera(const Point3& origin, const Vec3& target,
    const Vec3& up, float fov, float aspect)
{
    Vec3 front_u  = unit(target - origin);
    Vec3 up_u = unit(up - front_u * dot(front_u, up));
    Vec3 right_u = cross(front_u, up_u);

    float w = tan(fov/2);
    float h = w / aspect;

    this->origin_ = origin;
    this->horizontal_ = 2 * w * right_u;
    this->vertical_   = 2 * h * up_u;
    this->bottomleft_ = front_u - h*up_u - w * right_u;
}


Ray PerspectiveCamera::windowToRay(const Vec3& uv) const
{
    Vec3 target = bottomleft_ + uv.x() * horizontal_ + uv.y() * vertical_;
    return Ray(origin_, target);
}


CameraPtr PerspectiveCamera::fromDescription(const CameraDescription *desc)
{
    const PerspectiveCameraDescription *cam =
        dynamic_cast<const PerspectiveCameraDescription *>(desc);

    return CameraPtr(new PerspectiveCamera(cam->position,
                                           cam->target,
                                           cam->up,
                                           cam->field_of_view,
                                           cam->aspect_ratio));
}
