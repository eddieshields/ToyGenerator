from hydra import *

SetDecay("D0 => KS0 K+ K-")


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
Hydra().EvtMax = 10000
Hydra().AlgoSequence = seq
Hydra().Variables = tup.getVariables() 
Hydra().NThreads = 1
Hydra().TreeName = "d02kskk"
Hydra().OutputLocation = "output.root"
Hydra.run()