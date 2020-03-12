#!/bin/bash
cp /imports/*pp /building
cp /imports/CMakeLists.txt /building
cd /building
cmake .
make
cp app /imports
