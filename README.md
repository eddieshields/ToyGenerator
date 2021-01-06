![CMake](https://github.com/eddieshields/ToyGenerator/workflows/CMake/badge.svg)

# Hydra

Hydra is a package for generating toys that is fast, easily configurable and hopefully user friendly. 




## Compilation

First clone the respository,

```bash
https://github.com/eddieshields/ToyGenerator.git
```

and fetch necessary external libraries

```bash
git submodule update --init --recursive
```

If you are working on lxplus you will need to set up the right environment with 

```bash 
source /cvmfs/sft.cern.ch/lcg/views/setupViews.sh LCG_97python3 x86_64-centos7-gcc8-opt
```

Then

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

Each subsequent time you use this package, call 

```bash
. setup.sh
```

from the root directory.

### Interactive Hydra

Hydra can be used in an interactive python session. Simply call

```bash
Hydra
```

from the directory root to load and interactive python session with Hydra pre-configured. You can
additionally call options files this way by 

```bash
Hydra path/to/options/file
```


### Python environment

For using the python version of this program I would recommend setting up a python virtual
environment and working in that.

```bash
python3 -m venv /path/to/new/virtual/environment
```

To activate the virtual environment then do 

```bash
source /path/to/new/virtual/environment
```

and then,

```bash
pip install -r requirements.txt
```

This should set up your environments with all the necessary packages.

## Configuration

Configuration in Hydra is based on the principle of a series of algorithms acting on events.
Create a sequence and then add algorithms to it in order using the

```cpp
sequence.addAlgorithm(Algorithm)
```

method.
