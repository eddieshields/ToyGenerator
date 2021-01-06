import ROOT as r 
r.gSystem.Load('build/libHYDRA')

# Import core Hydra.
from ROOT import ( Hydra,
                   Clock,
                   DecayDescriptor,
                   Event,
                   Particle,
                   ParticleStore,
                   #PyAlgorithm,
                   Random,
                   Sequence
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
                   Tupling
                 )

def SetDecay(decay):
    r.Hydra.SetDecay(decay)
    return

def printc(inp):
    print("\033[1;31m"+inp+"\033[0m\n")