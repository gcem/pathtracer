cmake_minimum_required(VERSION 3.10)

project(pathTracer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(pathTracer main.cpp)

configure_file(config.h.in config.h)

target_include_directories(pathTracer PUBLIC
    "${PROJECT_BINARY_DIR}"
)