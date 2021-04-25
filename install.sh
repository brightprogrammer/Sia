#!/bin/zsh
cd build
rm -vf CMakeCache.txt
cmake .. -DPROJECT_VERSION_MAJOR=0 -DPROJECT_VERSION_MINOR=0 -DPROJECT_VERSION_PATCH=1 -DPROJECT_VERSION_TWEAK=0
make -j4
cd ..
ln -svf build/siac siac