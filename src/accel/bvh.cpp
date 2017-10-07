#include "accel/bvh.h"

#include <algorithm>



template<int n>
bool coord_lt(const SurfacePtr& s1, const SurfacePtr& s2) {
    return (s1->bbox.min()[n] < s2->bbox.min()[n]);
}


template <int n>
BVH::Tree* build(const std::vector<SurfacePtr>::iterator begin,
    const std::vector<SurfacePtr>::iterator end)
{
    constexpr int nn = (n+1)%3;
    if (begin == end)
        return nullptr;

    BVH::Tree* node = new BVH::Tree();
    if (begin + 1 == end) {
        node->surface = *begin;
        node->left = nullptr;
        node->right = nullptr;
        node->bbox = (*begin)->bbox;
    }
    else {
        std::sort(begin, end, coord_lt<n>);
        auto mid = begin + std::distance(begin, end)/2;
        node->left = build<nn>(begin, mid);
        node->right = build<nn>(mid, end);
        node->bbox = BBox::wrap(node->left->bbox, node->right->bbox);
    }
    return node;
}

BVH::BVH(std::vector<SurfacePtr>& surfs)
{
    root_ = build<1>(surfs.begin(), surfs.end());
}


BVH::~BVH()
{
    delete root_;
}


static bool hit_R(const BVH::Tree *node, const Ray &ray, Hit& hit, float& error)
{
    Hit temp_hit;
    if (!node)
        return false;

    if (!node->bbox.intersect(ray))
        return false;

    if (node->surface)
        return node->surface->hit(ray, hit, error);

    bool hit_left, hit_right;
    hit_left = hit_R(node->left, ray, hit, error);

    if (hit_left) {
        hit_right = hit_R(node->right, ray, temp_hit, error);
        if (hit_right && temp_hit.t < hit.t)
            hit = temp_hit;
        return true;
    }
    else {
        return hit_R(node->right, ray, hit, error);
    }
}


bool BVH::hit(const Ray &ray, Hit& hit, float& error) const
{
    return hit_R(root_, ray, hit, error);
}
