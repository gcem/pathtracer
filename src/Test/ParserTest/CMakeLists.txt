add_executable(ParserTest ParserTest.cpp PLYReaderTest.cpp)

target_link_libraries(ParserTest
    PUBLIC
    LinearAlgebra Objects Parser Mocks
    PRIVATE
    gtest gtest_main gmock pthread)

configure_file(Scenes/SimpleScene.xml Scenes/SimpleScene.xml COPYONLY)
configure_file(Scenes/SimplePolygons.ply Scenes/SimplePolygons.ply COPYONLY)

gtest_discover_tests(ParserTest)