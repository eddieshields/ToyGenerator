from hydra import *

SetDecay("D0 => K+ pi- pi+ pi-")

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
Hydra().EvtMax = 10000
Hydra().AlgoSequence = seq
Hydra().Variables = tup.getVariables()
Hydra().NThreads = 1
Hydra().TreeName = "d02k3pi"
Hydra().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root"
Hydra.run()