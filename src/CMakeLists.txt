cmake_minimum_required(VERSION 3.10)

project(PathTracer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(COMPILER)

configure_file(Config.h.in Config.h)

add_subdirectory(LinearAlgebra)
add_subdirectory(Objects)
add_subdirectory(Test)

add_executable(PathTracer main.cpp)

target_link_libraries(PathTracer PUBLIC LinearAlgebra Objects)

target_include_directories(PathTracer PUBLIC
    "${PROJECT_BINARY_DIR}"
)