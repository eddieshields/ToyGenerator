from hydra import *

# option parser
import argparse
parser = argparse.ArgumentParser(description='Options for generating phasespace toys')
parser.add_argument('--nevents',  default=1000,              type=int)
parser.add_argument('--nthreads', default=1,                 type=int)
parser.add_argument('--decay',    default="D0 => KS0 K+ K-", type=str)
parser.add_argument('--output',   default='Output.root',     type=str)
parser.add_argument('--treename', default='DecayTree',       type=str)
args = parser.parse_args()

# Set the decay
SetDecay("D0 => KS0 K+ K-")

# Configure algorithms
gen = Generator("Generator")
acc = Accept("Accept")
tup = Tupling("Tupling")
tup.addMass()
tup.addCompositeMass()

# Make sequence
seq = MakeSequence(gen,acc,tup)

# Configure Hydra.
Hydra().EvtMax = args.nevents
Hydra().AlgoSequence = seq
Hydra().Variables = tup.getVariables()
Hydra().NThreads = args.nthreads
Hydra().TreeName = args.treename
Hydra().OutputLocation = args.output
Hydra.run()