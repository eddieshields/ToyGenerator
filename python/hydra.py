import ROOT as r 
r.gSystem.Load('build/libHYDRA')


# Import core Hydra.
from ROOT import ( Hydra,
                   DecayDescriptor,
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
                   D02K3Pi,
                   Decay3Body,
                   Decay3BodyMixing,
                   Efficiency,
                   EventParam,
                   Generator,
                   ParticleParam,
                   Tupling
                 )

# Import Dalitz Model.
from ROOT.DalitzModel import ( Amplitude,
                               Coefficient,
                               ConfigFile,
                               ConfigureAmplitude,
                               LineShape,
                               Parameter,
                               PhaseSpace,
                               Resonance
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
    gRandom.SetSeed(seed)