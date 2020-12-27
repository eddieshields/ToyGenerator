from hydra import *
hy = Hydra()


vars = ["pdf","weight","t","K_q"]
# Configure algorithms.
gen = r.Generator("Generator",1.8645,0.49368,0.13957,0.13957,0.13957)
eff = r.Efficiency("Efficiency")
#amp = r.Amplitude("Amplitude")
amp = r.D02K3Pi("D02K3Pi")
acc = r.Accept("Accept")
acc.setMaxPdf(0.4)
tup = r.Tupling("Tupling")
tup.setVariables(vars)


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
hy().Variables = vars
hy().NThreads = 1
hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root"

hy.run()