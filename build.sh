#!/bin/bash

echo "Fetching external libraries..."
git submodule update --init --recursive

if [[ $(hostname -s) = lxplus* ]]; then
  echo "Setting lxplus environment..."
  source /cvmfs/sft.cern.ch/lcg/views/setupViews.sh LCG_97python3 x86_64-centos7-gcc8-opt
fi

echo "Building..."
mkdir build
cd build
cmake ..
make
cd ..

echo "Setup..."
source setup.sh
