#!/bin/bash
# Currently doesnt work.

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../CMake/ToolChain-mingw32.cmake ..
make