add_library(AccelerationStructures BruteForce.cpp BoundingBox.cpp BoundingVolumeHierarchy.cpp KDTree.cpp KDTreeNode.cpp)

target_include_directories(AccelerationStructures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(AccelerationStructures PUBLIC Objects LinearAlgebra)