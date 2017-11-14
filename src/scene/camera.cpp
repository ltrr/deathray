#include "scene/camera.h"
#include "util/random.h"


PerspectiveCamera::PerspectiveCamera()
    : origin_(0, 0, 0),
      bottomleft_(-1, -1, 0),
      vertical_(0, 2, 0),
      horizontal_(2, 0, 0) {}


PerspectiveCamera::PerspectiveCamera(const Point3& origin, const Vec3& target,
    const Vec3& up, float fov, float aspect)
    : PerspectiveCamera(origin, target, up, fov, aspect, 1, 0) { }


PerspectiveCamera::PerspectiveCamera(const Point3& origin, const Vec3& target,
    const Vec3& up, float fov, float aspect, float f, float aperture)
    : f_(f), aperture_(aperture)
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

    Ray ray(origin_, unit(target));
    if (aperture_ > 0.0f) {
        Point3 f_point = ray.at(f_);
        auto delta = rand_on_s1();
        Vec3 du = (delta[0] * aperture_ / len(horizontal_)) * horizontal_;
        Vec3 dv = (delta[1] * aperture_ / len(vertical_)) * vertical_;
        Point3 origin = ray.origin() + du + dv;
        return Ray(origin, unit(f_point - origin));
    }
    else {
        return ray;
    }
}


CameraPtr PerspectiveCamera::fromDescription(const CameraDescription *desc)
{
    const PerspectiveCameraDescription *cam =
        dynamic_cast<const PerspectiveCameraDescription *>(desc);

    return CameraPtr(new PerspectiveCamera(cam->position,
                                           cam->target,
                                           cam->up,
                                           cam->field_of_view,
                                           cam->aspect_ratio,
                                           cam->focus_distance,
                                           cam->aperture));
}


OrthogonalCamera::OrthogonalCamera()
    : direction_(0, 0, -1),
      bottomleft_(-1, -1, 0),
      vertical_(0, 2, 0),
      horizontal_(2, 0, 0) { }


OrthogonalCamera::OrthogonalCamera(const Point3& origin, const Vec3& target,
    const Vec3& up, float width, float height)
{
    Vec3 front_u  = unit(target - origin);
    Vec3 up_u = unit(up - front_u * dot(front_u, up));
    Vec3 right_u = cross(front_u, up_u);

    float w = width / 2;
    float h = height / 2;

    this->direction_ = front_u;
    this->horizontal_ = 2 * w * right_u;
    this->vertical_   = 2 * h * up_u;
    this->bottomleft_ = origin - h*up_u - w * right_u;
}


Ray OrthogonalCamera::windowToRay(const Vec3& uv) const
{
    Point3 origin = bottomleft_ + uv.x() * horizontal_ + uv.y() * vertical_;
    return Ray(origin, direction_);
}


CameraPtr OrthogonalCamera::fromDescription(const CameraDescription *desc)
{
    const OrthogonalCameraDescription *cam =
        dynamic_cast<const OrthogonalCameraDescription *>(desc);

    return CameraPtr(new OrthogonalCamera(cam->position,
                                           cam->target,
                                           cam->up,
                                           cam->width,
                                           cam->height));
}
