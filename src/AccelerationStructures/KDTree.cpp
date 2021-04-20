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
    return root->intersect(ray, normalOut);
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
}