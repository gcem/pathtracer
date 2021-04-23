add_library(Parser XMLParser.cpp Parser.cpp PLYReader.cpp)

target_link_libraries(Parser PUBLIC Objects ThirdParty Options)

target_include_directories(Parser INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})