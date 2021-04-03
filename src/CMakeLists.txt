cmake_minimum_required(VERSION 3.10)

project(PathTracer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(COMPILER)

add_subdirectory(LinearAlgebra)
add_subdirectory(Objects)
add_subdirectory(Test)

add_executable(PathTracer main.cpp)

target_link_libraries(PathTracer PUBLIC LinearAlgebra Objects)

configure_file(Config.h.in Config.h)

target_include_directories(PathTracer PUBLIC
    "${PROJECT_BINARY_DIR}"
)