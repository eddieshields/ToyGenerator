from hydra import *
hy = Hydra()
hy.setDecay("D0 => K+ pi- pi+ pi-")


def pyfunc(ev):
    ev["mSq12"] = 0.8
    ev.pdf = 1

# Configure algorithms.
gen = r.Generator("Generator")
amp = r.D02K3Pi("D02K3Pi")
eff = r.PyAlgorithm("Eff",pyfunc) 
acc = r.Accept("Accept")
acc.setMaxPdf(0.4)
tup = r.Tupling("Tupling")
tup.addMass()


# Create sequence.
seq = r.Sequence()
seq.addAlgorithm(gen)
seq.addAlgorithm(amp)
#seq.addAlgorithm(eff)
seq.addAlgorithm(acc)
seq.addAlgorithm(tup)
seq.printAlgorithmSequence()

# Configure Hydra.
hy().EvtMax = 10000
hy().TreeName = "d02kshh"
hy().AlgoSequence = seq
hy().Variables = tup.getVariables()
hy().NThreads = 1
hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root"

hy.run()