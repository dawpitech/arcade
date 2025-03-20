#!/usr/bin/env bash
rm -rf ./build/
mkdir ./build/ && cd ./build/
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
ls arcade lib/
