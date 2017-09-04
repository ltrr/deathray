#include "triangle.h"

#include <limits>
#include "vector.h"
#include "ray.h"


const float EPS = 100 * std::numeric_limits<float>::epsilon();


Triangle::Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3,
    MaterialPtr mat)
    : origin(p1), material(mat), u(p2 - p1), v(p3 - p1)
{
    n = unit(cross(u, v));
}


Triangle::Triangle(const Vec3& p1, const Vec3& p2, const Vec3& p3,
    const Vec3& normal, MaterialPtr mat)
    : origin(p1), material(mat), u(p2 - p1), v(p3 - p1)
{
    n = unit(cross(u, v));
    if (dot(n, normal) < 0) n *= -1;
    //n = unit(normal);
}


bool Triangle::hit(const Ray &ray, float t_min, float t_max, Hit& hit) const
{
    float dn = dot(ray.dir(), n);
    if (dn == 0) // parallel
        return false;

    float t = dot(origin - ray.origin(), n) / dn;

    if (!(t_min < t && t <= t_max))
        return false;

    Vec3 r = ray.at(t) - origin;

    float uu = dot(u, u);
    float uv = dot(u, v);
    float vv = dot(v, v);
    float ru = dot(r, u);
    float rv = dot(r, v);
    float d = uu*vv - uv*uv;

    float su = (ru*vv - rv*uv) / d;
    float sv = (rv*uu - ru*uv) / d;

    if (su >= -EPS && sv >= -EPS && su + sv <= 1+EPS) {
        hit.t = t;
        hit.point = ray.at(t);
        hit.normal = unit(dn > 0 ? -n : n);
        hit.material = this->material;
        return true;
    }
    else {
        return false;
    }
}
