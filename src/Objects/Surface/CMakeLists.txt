add_library(Surface Mesh.cpp Triangle.cpp Sphere.cpp)

target_include_directories(Surface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${PROJECT_BINARY_DIR})