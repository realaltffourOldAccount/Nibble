#!/bin/bash
# Currently doesnt work.

mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../CMake/ToolChain-mingw32.cmake ..
ninja -j8