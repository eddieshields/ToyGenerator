from hydra import *
hy = Hydra()

# Configure algorithms.
gen = r.Generator("Generator",1.9,0.4,0.4,0.5)
eff = r.Efficiency("Efficiency")
amp = r.Amplitude("Amplitude")
# Create sequence.
seq = r.Sequence(gen,eff,amp)

# Configure Hydra.
hy().EvtMax = 10000
hy().TreeName = "d0kshh"
hy().AlgoSequence = seq