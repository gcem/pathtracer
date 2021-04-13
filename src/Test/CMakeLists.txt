include(GoogleTest)
add_executable(PathTracerUnitTests
    VectorTest.cpp MatrixTest.cpp RayTest.cpp CameraTest.cpp
    TriangleTest.cpp SphereTest.cpp MaterialTest.cpp MeshTest.cpp
    PathTracerTest.cpp)

target_link_libraries(PathTracerUnitTests
    PUBLIC
    LinearAlgebra Objects Parser Mocks PathTracer
    PRIVATE
    gtest gtest_main gmock pthread
)

add_subdirectory(ParserTest)
add_subdirectory(ImageTest)
add_subdirectory(Mocks)

gtest_discover_tests(PathTracerUnitTests)