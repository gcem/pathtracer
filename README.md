# *Path Tracer*

# Introduction

Path Tracer for Advanced Ray Tracing (CENG 795) course at METU.

# Building

This project uses Google Test commit #6c5c4554 (version 1.10.x should do) and pnglib version 1.6.37. These libraries are not included in the repository. You only need pnglib if you will not run the tests.

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
./PathTracerApp --help
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