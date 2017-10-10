#include "surface/triangle.h"

#include "util/math.h"
#include "util/ray.h"
#include "util/vector.h"


Triangle::Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3,
    MaterialPtr mat)
    : origin_(p1), material_(mat), u_(p2 - p1), v_(p3 - p1),
      Surface({ min(p1, min(p2, p3)), max(p1, max(p2, p3)) })
{
    n_ = unit(cross(u_, v_));
}


Triangle::Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3,
    const Vec3& normal, MaterialPtr mat)
    : origin_(p1), material_(mat), u_(p2 - p1), v_(p3 - p1),
      Surface({min(p1, min(p2, p3)), max(p1, max(p2, p3))})
{
    n_ = unit(cross(u_, v_));
    if (dot(n_, normal) < 0) n_ *= -1;
}


bool Triangle::hit(const Ray &ray, Hit& hit, float& error) const
{
    float dn = dot(ray.dir(), n_);
    if (dn == 0) // parallel
        return false;

    float t = dot(origin_ - ray.origin(), n_) / dn;

    if (!ray.over(t))
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

    if (su >= -FLOAT_EPS && sv >= -10*FLOAT_EPS && su + sv <= 1+FLOAT_EPS) {
        hit.t = t;
        hit.point = ray.at(t);
        hit.normal = unit(dn > 0 ? -n_ : n_);
        hit.material = material_;
        error = t * 1e-3f;
        return true;
    }
    else {
        return false;
    }
}
