add_library(Objects Ray.cpp)

target_link_libraries(Objects PUBLIC LinearAlgebra)

target_include_directories(Objects INTERFACE ${CURRENT_SOURCE_DIR})