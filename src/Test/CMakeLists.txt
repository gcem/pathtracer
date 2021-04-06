include(GoogleTest)
add_executable(PathTracerUnitTests
    VectorTest.cpp MatrixTest.cpp RayTest.cpp CameraTest.cpp
    TriangleTest.cpp SphereTest.cpp MaterialTest.cpp MeshTest.cpp
    ParserTest.cpp)

target_link_libraries(PathTracerUnitTests
    PUBLIC
    LinearAlgebra Objects Parser
    PRIVATE
    gtest gtest_main gmock pthread
)

gtest_discover_tests(PathTracerUnitTests)