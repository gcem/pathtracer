add_executable(ParserTest ParserTest.cpp)

target_link_libraries(ParserTest
    PUBLIC
    LinearAlgebra Objects Parser Mocks
    PRIVATE
    gtest gtest_main gmock pthread)

configure_file(Scenes/SimpleScene.xml Scenes/SimpleScene.xml COPYONLY)
gtest_discover_tests(ParserTest)