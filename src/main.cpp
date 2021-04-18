#include "Config.hpp"
#include "GlobalOptions.hpp"
#include "PathTracer.hpp"
#include "XMLParser.hpp"
#include <argp.h>
#include <cstring>
#include <fstream>
#include <iostream>

struct argp argpParser;

error_t
parserFunction(int key, char* arg, argp_state* state)
{
    switch (key) {
        case 'a':
            if (strcmp(arg, "bf") == 0)
                Options::globalOptions.accelerationStructure =
                  Options::AccelerationStructureEnum::BruteForce;
            else if (strcmp(arg, "bb") == 0)
                Options::globalOptions.accelerationStructure =
                  Options::AccelerationStructureEnum::BoundingBox;
            else if (strcmp(arg, "bvh") == 0)
                Options::globalOptions.accelerationStructure =
                  Options::AccelerationStructureEnum::BoundingVolumeHierarchy;
            else {
                std::cout << "Unknown accelerator type \"" << arg << '"'
                          << std::endl;
                exit(1);
            }
            break;
        case ARGP_KEY_ARG:
            // argument for scene file name
            Options::globalOptions.sceneFileName = arg;
            break;
        case ARGP_KEY_NO_ARGS:
            // no scene file given
            {
                char name[] = "PathTracerApp";
                argp_help(&argpParser, stdout, ARGP_HELP_USAGE, name);
            }
            exit(1);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

void
parseArguments(int argc, char* argv[])
{
    static char versionString[64];
    sprintf(versionString,
            "PathTracer version %d.%d",
            PathTracer_VERSION_MAJOR,
            PathTracer_VERSION_MINOR);
    argp_program_version = versionString;

    struct argp_option options[] = {
        { "acceleration",
          'a',
          "type",
          0,
          "Acceleration structure to use with triangle meshes. Possible values "
          "are bf (brute force), bb (bounding box), bvh (bounding volume "
          "hierarchy)." },
        0
    };
    argpParser = { options, parserFunction, "SCENE-FILE", 0, 0, 0 };
    argp_parse(&argpParser, argc, argv, 0, 0, 0);
}

int
main(int argc, char* argv[])
{
    parseArguments(argc, argv);

    Parser::XMLParser parser;
    auto stream =
      std::ifstream(std::string(Options::globalOptions.sceneFileName));
    if (!stream.is_open()) {
        std::cout << "Could not open file \""
                  << Options::globalOptions.sceneFileName << '"' << std::endl;
        exit(1);
    }

    bool success = parser.parse(stream);
    if (!success) {
        std::cout << "Could not read file \""
                  << Options::globalOptions.sceneFileName << '"' << std::endl;
        exit(1);
    }

    auto scene = parser.getScene();
    PathTracer::PathTracer tracer;
    tracer.trace(scene);

    return 0;
}