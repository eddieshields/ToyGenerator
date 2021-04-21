from hydra import *

import argparse
parser = argparse.ArgumentParser(description='Submit toy generation jobs to ganga')
parser.add_argument('-s','--seed',  type=int, default=0,           help='Random seed')
parser.add_argument('-m','--model', type=str, default='belle2010', help='Model')
args = parser.parse_args()


SetDecay("D0 => K_S0 K+ K-")
SetSeed(args.seed)

# Configure algorithms.
# Generate events according to decay.
gen = Generator("Generator")
# Set event pdf value according to an amplitude model with mixing.
amp = Decay3BodyMixing("D02KSKKAmplitude","cfg/"+args.model+".cfg")
# Accept or reject event.
acc = Accept("Accept")
acc.setMaxPdf(652.23)
# Add variables to be saved in ntuple.
tup = Tupling("Tupling")
tup.addCharge()
tup.addTime()
tup.addCompositeMass()


# Create sequence.
seq = Sequence()
seq.addAlgorithm(gen)
seq.addAlgorithm(amp)
seq.addAlgorithm(acc)
seq.addAlgorithm(tup)
seq.printAlgorithmSequence()

# Configure Hydra.
Hydra().EvtMax = 10000
Hydra().AlgoSequence = seq
Hydra().Variables = tup.getVariables()
Hydra().NThreads = -1
Hydra().TreeName = "d02kskk.root"
Hydra().OutputLocation = "d02kskk_"+str(args.seed)+".root"
Hydra.run()
