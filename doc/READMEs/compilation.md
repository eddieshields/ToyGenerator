# Compilation

After cloning the directory, fetch external libraries by

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