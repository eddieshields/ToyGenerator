from hydra import *
from Utils import PyAlgorithm
hy = Hydra()
hy.setDecay("D0 => K+ pi- pi+ pi-")


def pyfunc(ev):
    ev["mSq12"] = ev.particle(1).momentum().M() + ev.particle(2).momentum().M()
    return

# Configure algorithms.
gen = r.Generator("Generator")
amp = r.D02K3Pi("D02K3Pi")
tes = r.PyAlgorithm("pyfunc",pyfunc)
acc = r.Accept("Accept")
acc.setMaxPdf(0.4)
tup = r.Tupling("Tupling")
tup.addMass()
tup.addCharge()
tup.addTime()
tup.addEventInfo()

#R = amp.getR(gen)


# Create sequence.
seq = r.Sequence()
seq.addAlgorithm(gen)
seq.addAlgorithm(amp)
seq.addAlgorithm(tes)
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

hy.runPython()