#!/bin/bash

rm -r -f build
mkdir build
cd build
emconfigure cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DEMSCRIPTEN=True ..
ninja -j8