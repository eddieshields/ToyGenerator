from hydra import *

SetDecay("D0 => K_S0 K+ K-")


# Configure algorithms.
# Generate events according to decay.
gen = Generator("Generator")
# Set event pdf value according to an amplitude model with mixing.
amp = Decay3BodyMixing("D02KSKKAmplitude","cfg/belle2010.cfg")
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
Hydra().TreeName = "d02kskk"
Hydra().OutputLocation = "d02kskk.root"
Hydra.run()
