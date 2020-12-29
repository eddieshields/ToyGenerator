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

Then

```bash
mkdir build
cd build
cmake ..
make
cd ..
```

## Configuration
Configuration in Hydra is based on the principle of a series of algorithms acting on events.
Create a sequence and then add algorithms to it in order using the 

```cpp
sequence.addAlgorithm(Algorithm)
```

method.