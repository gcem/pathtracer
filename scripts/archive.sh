#! /bin/bash

# this script should be run from the base directory of project:
# 
# $ ./scripts/archive.sh
#
# output will be placed into build directory

tar --exclude="**/.gitignore" --exclude="scenes" --exclude="build" --exclude="doc" -czf build/pathtracer.tar.gz *