#include "util/bbox.h"
#include <iostream>

template<int x, int y, int z>
bool intersect2(const Ray& r, const Point3& origin, const Point3& delta)
{
    Vec3 dir = r.dir();
    if (dir[z] == 0)
        return false;

    float t0 = (origin[z] - r.origin()[z]) / dir[z];
    if (t0 < 0)
        return false;

    Vec3 p = r.at(t0);
    float u = (p[x] - origin[x]) / delta[x];
    float v = (p[y] - origin[y]) / delta[y];

    //std::cerr << "u=" << u << " v=" << v << '\n';

    return (u >= 0 && u <= 1 && v >= 0 && v <= 1);
}


bool BBox::intersect(const Ray& r)
{
    if (inside(r.origin()))
        return true;

    return (
        intersect2<0,1,2>(r, min_, max_-min_)
        || intersect2<1,2,0>(r, min_, max_-min_)
        || intersect2<2,0,1>(r, min_, max_-min_)
        || intersect2<0,1,2>(r, max_, min_-max_)
        || intersect2<1,2,0>(r, max_, min_-max_)
        || intersect2<2,0,1>(r, max_, min_-max_)
    );
}


bool BBox::intersect(const BBox& box)
{
    return (box.min_.x() <= max_.x()
         && box.min_.y() <= max_.y()
         && box.min_.z() <= max_.z()
         && box.max_.x() >= min_.x()
         && box.max_.y() >= min_.y()
         && box.max_.z() >= min_.z());
}


BBox BBox::wrap(const BBox& box1, const BBox& box2)
{
    return { min(box1.min_, box2.min_), max(box1.max_, box2.max_) };
}
