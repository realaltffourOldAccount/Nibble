#!/bin/bash

rm -r -f build
mkdir build
cd build
emconfigure cmake -DCMAKE_BUILD_TYPE=Release -DEMSCRIPTEN=True ..
make -j