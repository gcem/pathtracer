include(GoogleTest)
add_executable(PathTracerUnitTests VectorTest.cpp)

target_link_libraries(PathTracerUnitTests
    PUBLIC
    LinearAlgebra Objects
    PRIVATE
    gtest gtest_main gmock pthread
)

gtest_discover_tests(PathTracerUnitTests)