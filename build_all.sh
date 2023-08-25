#! /bin/bash

# remove old build files
rm -r build
rm -r bin

# Generate Build Files
cmake -S . -B build

# Buid Executables
cmake --build build
