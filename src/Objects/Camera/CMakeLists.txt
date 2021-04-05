add_library(Camera Camera.cpp PerspectiveCamera.cpp)

target_include_directories(Camera INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Camera PUBLIC LinearAlgebra Objects)