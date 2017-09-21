#ifndef DEATHRAY_BBOX_H_
#define DEATHRAY_BBOX_H_

#include "util/vector.h"
#include "util/ray.h"

class BBox
{
private:
    Point3 min_, max_;

public:
    BBox() {}

    BBox(const Point3& p1, const Point3& p2)
        : min_(min(p1, p2)), max_(max(p1, p2)) {}

    inline bool inside(const Point3& p)
    {
        return (min_.x() <= p.x() && p.x() <= max_.x()
             && min_.y() <= p.y() && p.y() <= max_.y()
             && min_.z() <= p.z() && p.z() <= max_.z());
    }

    bool intersect(const Ray& r);

    bool intersect(const BBox& box);

    static BBox wrap(const BBox& box1, const BBox& box2);
};

#endif // DEATHRAY_BBOX_H_
