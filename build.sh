#!/bin/bash

echo "Fetching external libraries..."
git submodule update --init --recursive

echo "Setting lxplus environment..."
source /cvmfs/sft.cern.ch/lcg/views/setupViews.sh LCG_97python3 x86_64-centos7-gcc8-opt]

echo "Building..."
mkdir build
cd build
cmake ..
make
cd ..

echo "Setup..."
. setup.sh