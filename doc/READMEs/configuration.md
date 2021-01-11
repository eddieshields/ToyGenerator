# Configuration

The easiest way to configure a series of algorithms is by writing an options file in python.
The basic structure of an options file is:

- Import Hydra
- Set the decay
- Configure algorithms
- Add algorithms to a sequence
- Set Hydra options
- Call hydra ```run()``` function

An example options file can be found [here](../../options/example.py)

The current available algorithms can be found in [algorithms/](../../algorithms/). The current list is:

- Accept
- Amplitude
- CompositeParam
- CustomParam
- D02K3Pi
- Decay3Body
- Decay3BodyMixing
- Efficiency
- EventParam
- Generator
- Param
- ParticleParam
- Tupling

## Import Hydra

Importing the package is done by 

```python
from hydra import *
```

## Set the decay

The most important thing to do when starting an options file is to set the decay. This is used globally throughout the package to configure algorithms.

```python
SetDecay( <decay> )
```

## Configure Algorithms

The create the algorithms you want to use. For example if you wanted to generate events and generate variables you would do 

```python
gen = Generator("Generator")
tup = Tupling("Tuping")
# Add mass variables.
tup.addMass()
```

## Add algorithms to sequence

This is done by creating a sequence

``` python
seq = Sequence()
```

And then adding algorithms

```python
seq.addAlgorithm(gen)
seq.addAlgorithm(tup)
```

or there is a helper function

```python
seq = MakeAlgorithm(gen,tup)
```

## Set Hydra options

Hydra has a series of options that can be configured through the () operator.

- EvtMax
- NThreads
- TreeName
- TreeTitle
- OutputLocation
- Variables
- AlgoSequence

i.e to set Hydra to generate 1000 events you would do

```python
Hydra().EvtMax = 1000
```

## Run Hydra

Finally run hydra by calling

```python
Hydra.run()
```