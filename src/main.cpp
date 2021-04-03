#include "Config.h"
#include <iostream>

int
main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << argv[0] << " version " << pathTracer_VERSION_MAJOR << "."
                  << pathTracer_VERSION_MINOR << std::endl;
        exit(1);
    }
    return 0;
}