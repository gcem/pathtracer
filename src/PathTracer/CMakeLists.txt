add_library(PathTracer PathTracer.cpp)

target_include_directories(PathTracer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PathTracer PUBLIC Objects LinearAlgebra Parser Image PRIVATE Options pthread)