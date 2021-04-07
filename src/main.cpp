#include "Config.hpp"
#include "PathTracer.hpp"
#include "XMLParser.hpp"
#include <fstream>
#include <iostream>

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << argv[0] << " version " << PathTracer_VERSION_MAJOR << "."
                  << PathTracer_VERSION_MINOR << std::endl;
        // todo: take executable name from CMake
        std::cout << "Usage: PathTracerApp sceneFile.xml" << std::endl;
        exit(1);
    }

    Parser::XMLParser parser;
    auto stream = std::ifstream(std::string(argv[1]));
    bool success = parser.parse(stream);
    if (!success) {
        std::cout << "Could not read file " << argv[1] << std::endl;
        exit(1);
    }

    auto scene = parser.getScene();
    PathTracer::PathTracer tracer;
    tracer.trace(scene);

    return 0;
}