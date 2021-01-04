import sys, os
sys.path.append(os.getcwd()+'/python')
from hydra import *
from array import *
hy = Hydra()
hy.setDecay("D0 => KS0 K+ K-")


# Configure algorithms.
gen = r.Generator("Generator")
amp = r.Decay3BodyMixing("D02KSKKAmplitude","cfg/belle2010.cfg")
acc = r.Accept("Accept")
acc.setMaxPdf(652.23)
tup = r.Tupling("Tupling")
tup.addCharge()
tup.addTime()
tup.addCompositeMass()


# Create sequence.
seq = r.Sequence()
seq.addAlgorithm(gen)
seq.addAlgorithm(amp)
seq.addAlgorithm(acc)
seq.addAlgorithm(tup)
seq.printAlgorithmSequence()

# Configure Hydra.
hy().EvtMax = 10000
hy().AlgoSequence = seq
hy().Variables = tup.getVariables() 
hy().NThreads = 1
hy().TreeName = "d02kskk"
hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root"

hy.run()