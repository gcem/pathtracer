add_library(Objects Ray.cpp PointLight.cpp Material.cpp)

add_subdirectory(Surface)
add_subdirectory(Camera)

target_link_libraries(Objects PUBLIC LinearAlgebra Surface Camera)

target_include_directories(Objects INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})