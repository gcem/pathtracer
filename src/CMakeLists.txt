cmake_minimum_required(VERSION 3.10)

project(PathTracer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(COMPILER)

configure_file(Config.hpp.in Config.hpp)

enable_testing()

add_subdirectory(LinearAlgebra)
add_subdirectory(Objects)
add_subdirectory(Parser)
add_subdirectory(Test)
add_subdirectory(3rdParty)

add_executable(PathTracer main.cpp)

target_link_libraries(PathTracer PUBLIC LinearAlgebra Objects)

target_include_directories(PathTracer PUBLIC
    "${PROJECT_BINARY_DIR}"
)