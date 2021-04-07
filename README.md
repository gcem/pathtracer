# *Path Tracer*

# Introduction

Path Tracer for Advanced Ray Tracing (CENG 795) course at METU.

# Building

```
git clone git@github.com:gcem/pathtracer.git
mkdir pathtracer/build
cd pathtracer/build
cmake ../src
cmake --build .
```

Commands in the following sections should be run in `build` directory.

# Usage
```
./PathTracerApp scene.xml
```

# Testing
First follow [Building](#Building) part. Then, in the build directory:

```
./PathTracerUnitTests
```
CMake is also aware of the tests. To run the tests using CMake:
```
ctest .
```
Finally, tests run automatically when a branch is pushed to GitHub. You can view
the results in *Actions* tab.

# Documentation
In the base directory:
```
doxygen
```
Then view `doc/index.html` with a browser. You can experiment with other doxygen
options. Configuration is written in `Doxyfile`.