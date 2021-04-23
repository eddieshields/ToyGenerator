import ROOT as r 
r.gSystem.Load('build/libHYDRA')


# Import core Hydra.
from ROOT import ( Hydra,
                   DecayDescriptor,
                   gDescriptor,
                   Event,
                   Particle,
                   ParticleStore,
                   Sequence,
                   DistributeTask,
                   ThreadPool
                 )

# Import Utils.
from ROOT import ( Clock,
                   CorrelationUtils,
                   FourVector,
                   Random
                 )
  
# Import Algorithms.
from ROOT import ( Accept,
                   CompositeParam,
                   CustomParam,
                   D02K3Pi,
                   DalitzPlotEfficiency,
                   Decay3Body,
                   Decay3BodyMixing,
                   DecayTimeEfficiency,
                   Efficiency,
                   EventParam,
                   Generator,
                   Param,
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

def SetSeed(seed):
    Random.setSeed(seed)