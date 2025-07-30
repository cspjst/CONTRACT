#!/bin/bash
echo "Running CMAKE for OW2..."

# clean cache
rm -rf ../bin/CMakeCache.txt ../bin/CMakeFiles/

cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=DOS -D CMAKE_SYSTEM_PROCESSOR=I86 -S. -B ../bin
