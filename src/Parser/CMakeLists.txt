add_library(Parser XMLParser.cpp)

target_link_libraries(Parser PUBLIC Objects);

target_include_directories(Parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})