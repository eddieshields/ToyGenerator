import ROOT as r 
r.gSystem.Load('build/libHydra')

# Import ROOT random engine
from ROOT import gRandom

# Import core Hydra.
from ROOT import ( Hydra,
                   Clock,
                   DecayDescriptor,
                   Event,
                   Particle,
                   ParticleStore,
                   PyAlgorithm,
                   Random,
                   Sequence,
                   Utils
                 )
  
# Import Algorithms.
from ROOT import ( Accept,
                   Amplitude,
                   CompositeParam,
                   D02K3Pi,
                   Decay3Body,
                   Decay3BodyMixing,
                   Efficiency,
                   EventParam,
                   Generator,
                   ParticleParam,
                   Secondaries,
                   Tupling
                 )

# Create Hydra object.
Hydra = Hydra()

# Helper functions.
def SetDecay(decay):
    Hydra.SetDecay(decay)
    return

def printc(inp):
    print("\033[1;31m"+inp+"\033[0m\n")

def MakeSequence(*args):
    seq = Sequence()
    for alg in args:
        seq.addAlgorithm(alg)
    return seq

def printAlgorithmSequence():
    Hydra().AlgorithmSequence().printAlgorithmSequence()

def SetSeed(seed):
    Random.setSeed(seed)
    gRandom.SetSeed(seed)