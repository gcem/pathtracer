#include "KDTree.hpp"
#include "AccelerationStructureConstants.hpp"
namespace AccelerationStructures {
FloatT
KDTree::intersect(const Objects::Ray& ray, LinearAlgebra::Vec3& normalOut) const
{
    if (!root)
        return BoundingBox::intersect(ray, normalOut);
    if (!hitsBoundingBox(ray))
        return -1;
    return root->intersect(ray, normalOut, getMaxT(ray));
}

void
KDTree::build(std::vector<Objects::Triangle>&& triangles)
{
    if (triangles.size() <= KD_BRUTE_FORCE_THRESHOLD) {
        BoundingBox::build(std::move(triangles));
        return;
    }

    createBoundingBox(triangles);
    root = std::make_unique<KDTreeNode>();

    // start by dividing on the longest axis
    FloatT xLen = xMax - xMin;
    FloatT yLen = yMax - yMin;
    FloatT zLen = zMax - zMin;

    if (xLen > yLen && xLen > zLen)
        root->build(std::move(triangles), KDTreeNode::Axis::x);
    else if (yLen > zLen)
        root->build(std::move(triangles), KDTreeNode::Axis::y);
    else
        root->build(std::move(triangles), KDTreeNode::Axis::z);
}

FloatT
KDTree::getMaxT(const Objects::Ray& ray) const
{
    /**
     * See BoundingBox::hitsBoundingBox() for an explanation
     *
     */

    FloatT tMax = std::numeric_limits<FloatT>::infinity();

    // planes normal to x axis
    FloatT t1 = (xMin - ray.origin.x) / ray.direction.x;
    FloatT t2 = (xMax - ray.origin.x) / ray.direction.x;
    tMax = std::min(tMax, std::max(t1, t2));

    // planes normal to y axis
    t1 = (yMin - ray.origin.y) / ray.direction.y;
    t2 = (yMax - ray.origin.y) / ray.direction.y;
    tMax = std::min(tMax, std::max(t1, t2));

    // planes normal to z axis
    t1 = (zMin - ray.origin.z) / ray.direction.z;
    t2 = (zMax - ray.origin.z) / ray.direction.z;
    tMax = std::min(tMax, std::max(t1, t2));

    return tMax;
}
}