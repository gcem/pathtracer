# create the library for later
add_library(LinearAlgebra Vector.cpp Matrix.cpp)

target_include_directories(LinearAlgebra INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})