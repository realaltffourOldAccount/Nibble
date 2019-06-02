#!/bin/bash

mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../CMake/ToolChain-mingw64.cmake ..
ninja -j8