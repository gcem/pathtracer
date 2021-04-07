add_executable(ImageTest PNGExporterTest.cpp)

target_link_libraries(ImageTest PUBLIC Image PRIVATE gtest gtest_main pthread)