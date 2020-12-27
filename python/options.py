from hydra import *
hy = Hydra()

# Configure algorithms.
gen = r.Generator("Generator",1.8645,0.49368,0.49368,0.49767)
eff = r.Efficiency("Efficiency")
amp = r.Amplitude("Amplitude")
acc = r.Accept("Accept")
tup = r.Tupling("Tupling")

# Create sequence.
seq = r.Sequence()
seq.addAlgorithm(gen)
seq.addAlgorithm(eff)
seq.addAlgorithm(amp)
seq.addAlgorithm(acc)
seq.addAlgorithm(tup)
seq.printAlgorithmSequence()

# Configure Hydra.
hy().EvtMax = 100000
hy().TreeName = "d02kshh"
hy().AlgoSequence = seq
hy().Variables = ["mSq12","mSq13","mSq23"]
hy().NThreads = 1
hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root"

hy.run()