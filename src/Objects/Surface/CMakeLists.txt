add_library(Surface Surface.cpp Mesh.cpp Triangle.cpp Sphere.cpp)

target_include_directories(Surface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${PROJECT_BINARY_DIR})

target_link_libraries(Surface PUBLIC LinearAlgebra Objects AccelerationStructures)