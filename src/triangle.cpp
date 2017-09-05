#include "triangle.h"

#include <limits>
#include "vector.h"
#include "ray.h"


const float EPS = 100 * std::numeric_limits<float>::epsilon();


Triangle::Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3,
    MaterialPtr mat)
    : origin_(p1), material_(mat), u_(p2 - p1), v_(p3 - p1)
{
    n_ = unit(cross(u_, v_));
}


Triangle::Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3,
    const Vec3& normal, MaterialPtr mat)
    : origin_(p1), material_(mat), u_(p2 - p1), v_(p3 - p1)
{
    n_ = unit(cross(u_, v_));
    if (dot(n_, normal) < 0) n_ *= -1;
}


bool Triangle::hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
{
    float dn = dot(ray.dir(), n_);
    if (dn == 0) // parallel
        return false;

    float t = dot(origin_ - ray.origin(), n_) / dn;

    if (!(t_min < t && t <= t_max))
        return false;

    Vec3 r = ray.at(t) - origin_;

    float uu = dot(u_, u_);
    float uv = dot(u_, v_);
    float vv = dot(v_, v_);
    float ru = dot(r, u_);
    float rv = dot(r, v_);
    float d = uu*vv - uv*uv;

    float su = (ru*vv - rv*uv) / d;
    float sv = (rv*uu - ru*uv) / d;

    if (su >= -EPS && sv >= -EPS && su + sv <= 1+EPS) {
        hit.t = t;
        hit.point = ray.at(t);
        hit.normal = unit(dn > 0 ? -n_ : n_);
        hit.material = material_;
        return true;
    }
    else {
        return false;
    }
}
