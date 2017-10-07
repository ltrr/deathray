#ifndef DEATHRAY_BVH_H_
#define DEATHRAY_BVH_H_

#include <vector>
#include "surface/surface.h"
#include "util/bbox.h"


class BVH
{
public:
    struct Tree
    {
        BBox bbox;
        Tree* left;
        Tree* right;
        SurfacePtr surface;

        ~Tree() {
            if (left) delete left;
            if (right) delete right;
        }
    };

private:
    Tree* root_;

public:
    BVH(std::vector<SurfacePtr>& surfs);

    ~BVH();

    bool hit(const Ray &ray, Hit& hit, float& error) const;
};


typedef std::shared_ptr<BVH> BVHPtr;

#endif // DEATHRAY_BVH_H_
