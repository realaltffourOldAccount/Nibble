#!/bin/bash

mkdir build
cd build
emconfigure cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DEMSCRIPTEN=True ..
ninja -j8