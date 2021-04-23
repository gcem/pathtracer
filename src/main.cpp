#include "Config.hpp"
#include "GlobalOptions.hpp"
#include "PathTracer.hpp"
#include "XMLParser.hpp"
#include <argp.h>
#include <chrono>
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
                Options::accelerationStructure =
                  Options::AccelerationStructureEnum::BruteForce;
            else if (strcmp(arg, "bb") == 0)
                Options::accelerationStructure =
                  Options::AccelerationStructureEnum::BoundingBox;
            else if (strcmp(arg, "bvh") == 0)
                Options::accelerationStructure =
                  Options::AccelerationStructureEnum::BoundingVolumeHierarchy;
            else if (strcmp(arg, "kd") == 0)
                Options::accelerationStructure =
                  Options::AccelerationStructureEnum::KDTree;
            else {
                std::cout << "Unknown accelerator type \"" << arg << '"'
                          << std::endl;
                exit(1);
            }
            break;
        case 'd':
            Options::minDigits = std::stoi(arg);
            break;
        case 'o':
            Options::outputPrefix = arg;
            break;
        case ARGP_KEY_ARG:
            // argument for scene file name
            Options::sceneFileName = arg;
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
          "hierarchy), kd(k-d tree). Default is bvh." },
        { "digits",
          'd',
          "number",
          0,
          "A % in the file name gets replaced with numbers starting with 0 "
          "until there is no scene file with the name. This option sets the "
          "minimum number of digits to use. Current number will be padded with "
          "0's to match the given number of digits. Default is 0." },
        { "outdir",
          'o',
          "prefix",
          0,
          "Prefix to add to camera output file names. If this is a directory, "
          "it should end with a '/' character and the directory must exist." },
        0
    };
    argpParser = { options, parserFunction, "SCENE-FILE", 0, 0, 0 };
    argp_parse(&argpParser, argc, argv, 0, 0, 0);
}

int
main(int argc, char* argv[])
{
    parseArguments(argc, argv);

    auto indexPosition = Options::sceneFileName.find_first_of('%');
    if (indexPosition == std::string::npos) {
        Parser::XMLParser parser;
        bool success = parser.parse(Options::sceneFileName);
        if (!success) {
            std::cout << "Could not read file \"" << Options::sceneFileName
                      << '"' << std::endl;
            exit(1);
        }

        auto scene = parser.getScene();
        PathTracer::PathTracer tracer;
        tracer.trace(scene);
    } else {
        auto startTime = std::chrono::system_clock::now();

        auto fileNameBeginning =
          Options::sceneFileName.substr(0, indexPosition);
        auto fileNameEnd = Options::sceneFileName.substr(indexPosition + 1);
        for (int i = 0;; i++) {
            char fileName[256];

            // creates a string like "%s%04d%s"
            auto formatString = std::string("%s%0") +
                                std::to_string(Options::minDigits) +
                                std::string("d%s");
            snprintf(fileName,
                     sizeof(fileName),
                     formatString.c_str(),
                     fileNameBeginning.c_str(),
                     i,
                     fileNameEnd.c_str());

            Parser::XMLParser parser;
            bool success = parser.parse(fileName);
            if (!success) {
                std::cout << "Terminating loop at index " << i << std::endl;
                break;
            }

            auto scene = parser.getScene();
            PathTracer::PathTracer tracer;
            tracer.trace(scene);
        }

        auto endTime = std::chrono::system_clock::now();
        int totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                          endTime - startTime)
                          .count();
        std::cout << "All scenes took " << totalTime / 1000.0 << " seconds"
                  << std::endl;
    }

    return 0;
}