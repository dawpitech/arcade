#!/usr/bin/env bash

if [[ $1 == "--help" ]]; then
    echo "./buddy.sh [-d; for verbose output]"
    exit
fi

rm -rf ./build/
mkdir ./build/ && cd ./build/ || exit
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

if [[ $1 == "-d" ]]; then
    cmake --build . --verbose
else
    cmake --build .
fi

cd ..
ls arcade lib/
