#include "Config.hpp"
#include <iostream>

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << argv[0] << " version " << PathTracer_VERSION_MAJOR << "."
                  << PathTracer_VERSION_MINOR << std::endl;
        exit(1);
    }
    return 0;
}