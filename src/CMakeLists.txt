cmake_minimum_required(VERSION 3.10)

project(PathTracer VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(MULTITHREADED "Make use of multiple cores" ON)
option(USE_DOUBLE "Use double precision floating point numbers" OFF)

# force single thread for debugging configurations
if (${CMAKE_BUILD_TYPE})
    set(MULTITHREADED OFF)
endif()

configure_file(Config.hpp.in Config.hpp)

add_library(Options INTERFACE)
target_include_directories(Options INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_subdirectory(LinearAlgebra)
add_subdirectory(Objects)
add_subdirectory(AccelerationStructures)
add_subdirectory(Parser)
add_subdirectory(Image)
add_subdirectory(PathTracer)
add_subdirectory(Test)
add_subdirectory(3rdParty)

add_executable(PathTracerApp main.cpp)

target_link_libraries(PathTracerApp PUBLIC LinearAlgebra Objects PathTracer Parser Options)

target_include_directories(PathTracerApp PUBLIC
    "${PROJECT_BINARY_DIR}"
)