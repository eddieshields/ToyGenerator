from hydra import *

hy = Hydra()
hy.setDecay("D0 => K+ pi- pi+ pi-")

# Configure algorithms.
gen = r.Generator("Generator")
amp = r.D02K3Pi("D02K3Pi")
acc = r.Accept("Accept")
acc.setMaxPdf(5)
tup = r.Tupling("Tupling")
tup.addMass()
tup.addCharge()
tup.addTime()
tup.addEventInfo()


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
hy().TreeName = "d02k3pi"
hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root"
import pdb; pdb.set_trace()
hy.run()