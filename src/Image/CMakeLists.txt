add_library(Image PNGExporter.cpp)

target_include_directories(Image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Image PUBLIC LinearAlgebra png PRIVATE ThirdParty)