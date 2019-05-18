#!/bin/bash

rm -r -f build
mkdir build
cd build
emconfigure cmake -DCMAKE_BUILD_TYPE=Debug -DEMSCRIPTEN=True ..
make -j8