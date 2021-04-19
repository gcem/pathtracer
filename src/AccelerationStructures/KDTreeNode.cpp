#include "KDTreeNode.hpp"
#include <algorithm>

namespace AccelerationStructures {
FloatT
KDTreeNode::intersect(const Objects::Ray& ray,
                      LinearAlgebra::Vec3& normalOut) const
{
    if (!left)
        return BruteForce::intersect(ray, normalOut);

    switch (divisionAxis) {
        case Axis::x:
            if (ray.direction.x > 0) {
                // coordinates are increasing
                if (ray.origin.x > divisionPlane)
                    // origin at the upper side
                    return right->intersect(ray, normalOut);

                LinearAlgebra::Vec3 leftNormal, rightNormal;
                FloatT planeT =
                  (divisionPlane - ray.origin.x) / ray.direction.x;

                FloatT leftT = left->intersect(ray, leftNormal);
                if (leftT == -1)
                    return right->intersect(ray, normalOut);

                if (leftT <= planeT) {
                    normalOut = leftNormal;
                    return leftT;
                }

                FloatT rightT = right->intersect(ray, rightNormal);
                if (rightT == -1 || leftT < rightT) {
                    normalOut = leftNormal;
                    return leftT;
                }

                normalOut = rightNormal;
                return rightT;
            } else if (ray.direction.x < 0) {
                // coordinates are decreasing
                if (ray.origin.x <= divisionPlane)
                    // origin at the upper side
                    return left->intersect(ray, normalOut);

                LinearAlgebra::Vec3 leftNormal, rightNormal;
                FloatT planeT =
                  (divisionPlane - ray.origin.x) / ray.direction.x;

                FloatT rightT = right->intersect(ray, rightNormal);
                if (rightT == -1)
                    return left->intersect(ray, normalOut);

                if (rightT <= planeT) {
                    normalOut = rightNormal;
                    return rightT;
                }

                FloatT leftT = left->intersect(ray, leftNormal);
                if (leftT == -1 || rightT < leftT) {
                    normalOut = rightNormal;
                    return rightT;
                }

                normalOut = leftNormal;
                return leftT;
            } else {
                // parallel to division plane
                if (ray.origin.x <= divisionPlane)
                    return left->intersect(ray, normalOut);
                else
                    return right->intersect(ray, normalOut);
            }
            break;
        case Axis::y:
            if (ray.direction.y > 0) {
                // coordinates are increasing
                if (ray.origin.y > divisionPlane)
                    // origin at the upper side
                    return right->intersect(ray, normalOut);

                LinearAlgebra::Vec3 leftNormal, rightNormal;
                FloatT planeT =
                  (divisionPlane - ray.origin.y) / ray.direction.y;

                FloatT leftT = left->intersect(ray, leftNormal);
                if (leftT == -1)
                    return right->intersect(ray, normalOut);

                if (leftT <= planeT) {
                    normalOut = leftNormal;
                    return leftT;
                }

                FloatT rightT = right->intersect(ray, rightNormal);
                if (rightT == -1 || leftT < rightT) {
                    normalOut = leftNormal;
                    return leftT;
                }

                normalOut = rightNormal;
                return rightT;
            } else if (ray.direction.y < 0) {
                // coordinates are decreasing
                if (ray.origin.y <= divisionPlane)
                    // origin at the upper side
                    return left->intersect(ray, normalOut);

                LinearAlgebra::Vec3 leftNormal, rightNormal;
                FloatT planeT =
                  (divisionPlane - ray.origin.y) / ray.direction.y;

                FloatT rightT = right->intersect(ray, rightNormal);
                if (rightT == -1)
                    return left->intersect(ray, normalOut);

                if (rightT <= planeT) {
                    normalOut = rightNormal;
                    return rightT;
                }

                FloatT leftT = left->intersect(ray, leftNormal);
                if (leftT == -1 || rightT < leftT) {
                    normalOut = rightNormal;
                    return rightT;
                }

                normalOut = leftNormal;
                return leftT;
            } else {
                // parallel to division plane
                if (ray.origin.y <= divisionPlane)
                    return left->intersect(ray, normalOut);
                else
                    return right->intersect(ray, normalOut);
            }
            break;
        case Axis::z:
            if (ray.direction.z > 0) {
                // coordinates are increasing
                if (ray.origin.z > divisionPlane)
                    // origin at the upper side
                    return right->intersect(ray, normalOut);

                LinearAlgebra::Vec3 leftNormal, rightNormal;
                FloatT planeT =
                  (divisionPlane - ray.origin.z) / ray.direction.z;

                FloatT leftT = left->intersect(ray, leftNormal);
                if (leftT == -1)
                    return right->intersect(ray, normalOut);

                if (leftT <= planeT) {
                    normalOut = leftNormal;
                    return leftT;
                }

                FloatT rightT = right->intersect(ray, rightNormal);
                if (rightT == -1 || leftT < rightT) {
                    normalOut = leftNormal;
                    return leftT;
                }

                normalOut = rightNormal;
                return rightT;
            } else if (ray.direction.z < 0) {
                // coordinates are decreasing
                if (ray.origin.z <= divisionPlane)
                    // origin at the upper side
                    return left->intersect(ray, normalOut);

                LinearAlgebra::Vec3 leftNormal, rightNormal;
                FloatT planeT =
                  (divisionPlane - ray.origin.z) / ray.direction.z;

                FloatT rightT = right->intersect(ray, rightNormal);
                if (rightT == -1)
                    return left->intersect(ray, normalOut);

                if (rightT <= planeT) {
                    normalOut = rightNormal;
                    return rightT;
                }

                FloatT leftT = left->intersect(ray, leftNormal);
                if (leftT == -1 || rightT < leftT) {
                    normalOut = rightNormal;
                    return rightT;
                }

                normalOut = leftNormal;
                return leftT;
            } else {
                // parallel to division plane
                if (ray.origin.z <= divisionPlane)
                    return left->intersect(ray, normalOut);
                else
                    return right->intersect(ray, normalOut);
            }
            break;
        default:
            // doesn't happen but my compiler is complaining otherwise
            return -1;
    }
}

void
KDTreeNode::build(std::vector<Objects::Triangle>&& triangles, Axis divisionAxis)
{
    if (triangles.size() <= BRUTE_FORCE_THRESHOLD) {
        BruteForce::build(std::move(triangles));
        return;
    }

    this->divisionAxis = divisionAxis;

    // { divisionAxis coordinate of center, surface area }
    std::vector<std::pair<FloatT, FloatT>> data;
    data.reserve(triangles.size());

    FloatT totalArea = 0;

    // put centers of triangles into data array along with their area
    switch (divisionAxis) {
        case Axis::x:
            for (auto& triangle : triangles) {
                FloatT area = triangle.area();
                FloatT center =
                  (triangle.v1.x + triangle.v2.x + triangle.v3.x) / 3;
                data.push_back({ center, area });
                totalArea += area;
            }
            break;
        case Axis::y:
            for (auto& triangle : triangles) {
                FloatT area = triangle.area();
                FloatT center =
                  (triangle.v1.y + triangle.v2.y + triangle.v3.y) / 3;
                data.push_back({ center, area });
                totalArea += area;
            }
            break;
        case Axis::z:
            for (auto& triangle : triangles) {
                FloatT area = triangle.area();
                FloatT center =
                  (triangle.v1.z + triangle.v2.z + triangle.v3.z) / 3;
                data.push_back({ center, area });
                totalArea += area;
            }
            break;
    }

    // sort w.r.t. center coordinate
    std::sort(data.begin(), data.end());

    // find a coordinate that would make areas close to equal (doesn't consider
    // dividing triangles)
    FloatT area = 0;
    int next = 0;
    while (area < totalArea / 2) {
        area += data[next].second;
        next++;
    }

    divisionPlane = (data[next - 1].first + data[next].first) / 2;

    std::vector<Objects::Triangle> leftTriangles, rightTriangles;
    leftTriangles.reserve(next);
    rightTriangles.reserve(triangles.size() - next + 1);

    switch (divisionAxis) {
        case Axis::x:
            for (auto& triangle : triangles) {
                if (triangle.v1.x <= divisionPlane ||
                    triangle.v2.x <= divisionPlane ||
                    triangle.v3.x <= divisionPlane)
                    leftTriangles.push_back(triangle);
                if (triangle.v1.x > divisionPlane ||
                    triangle.v2.x > divisionPlane ||
                    triangle.v3.x > divisionPlane)
                    rightTriangles.push_back(triangle);
            }
            break;
        case Axis::y:
            for (auto& triangle : triangles) {
                if (triangle.v1.y <= divisionPlane ||
                    triangle.v2.y <= divisionPlane ||
                    triangle.v3.y <= divisionPlane)
                    leftTriangles.push_back(triangle);
                if (triangle.v1.y > divisionPlane ||
                    triangle.v2.y > divisionPlane ||
                    triangle.v3.y > divisionPlane)
                    rightTriangles.push_back(triangle);
            }
            break;
        case Axis::z:
            for (auto& triangle : triangles) {
                if (triangle.v1.z <= divisionPlane ||
                    triangle.v2.z <= divisionPlane ||
                    triangle.v3.z <= divisionPlane)
                    leftTriangles.push_back(triangle);
                if (triangle.v1.z > divisionPlane ||
                    triangle.v2.z > divisionPlane ||
                    triangle.v3.z > divisionPlane)
                    rightTriangles.push_back(triangle);
            }
            break;
    }

    // make sure number of triangles are decreasing as we go down the tree
    if (leftTriangles.size() == triangles.size() ||
        rightTriangles.size() == triangles.size()) {
        BruteForce::build(std::move(triangles));
        return;
    }

    left = std::make_unique<KDTreeNode>();
    right = std::make_unique<KDTreeNode>();

    // build children with next axis
    switch (divisionAxis) {
        case Axis::x:
            left->build(std::move(leftTriangles), Axis::y);
            right->build(std::move(rightTriangles), Axis::y);
            break;
        case Axis::y:
            left->build(std::move(leftTriangles), Axis::z);
            right->build(std::move(rightTriangles), Axis::z);
            break;
        case Axis::z:
            left->build(std::move(leftTriangles), Axis::x);
            right->build(std::move(rightTriangles), Axis::x);
            break;
    }
}
}