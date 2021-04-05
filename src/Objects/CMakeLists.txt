add_library(Objects Ray.cpp)

add_subdirectory(Surface)

target_link_libraries(Objects PUBLIC LinearAlgebra)

target_include_directories(Objects INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})