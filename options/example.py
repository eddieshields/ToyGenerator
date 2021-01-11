from hydra import *

SetDecay("D0 => KS0 K+ K-")

def mis_id(ev):
    ev.particle(1).m_mass = 0.13957


# Configure algorithms.
gen = Generator("Generator")
acc = Accept("Accept")
mis = PyAlgorithm("MisId",mis_id)
tup = Tupling("Tupling")
tup.addCharge()
tup.addTime()
tup.addCompositeMass()


# Create sequence.
seq = r.Sequence()
seq.addAlgorithm(gen)
seq.addAlgorithm(acc)
seq.addAlgorithm(tup)
seq.printAlgorithmSequence()

# Configure Hydra.
Hydra().EvtMax = 10000
Hydra().AlgoSequence = seq
Hydra().Variables = tup.getVariables() 
Hydra().NThreads = 10
Hydra().TreeName = "DecayTree"
Hydra().OutputLocation = "example_output.root"
Hydra.run()