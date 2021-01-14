from hydra import *

SetDecay("D0 => KS0 K+ K-")


# Configure algorithms.
# Generate events according to decay.
gen = Generator("Generator")
# Add secondary contamination
sec = Secondaries("Secondaries")
sec.LoadHistogram("/afs/cern.ch/user/e/eshields/cernbox/Analysis/branches/fitting/d02kskk-ycp/D02KSKKAnalysis/res/acceptance/Prompt_LL/Prompt_LL_secondaries_acceptance.root","secondaries")
sec.LoadFraction("/afs/cern.ch/user/e/eshields/cernbox/Analysis/branches/fitting/d02kskk-ycp/D02KSKKAnalysis/res/secondaries/Prompt_LL/sec_fractions_dist_Prompt_LL.root","ff","result")
# Set event pdf value according to an amplitude model with mixing.
amp = Decay3BodyMixing("D02KSKKAmplitude","cfg/belle2010.cfg")
amp.setX(0.004)
amp.setY(0.006)
# Accept or reject event.
acc = Accept("Accept")
acc.setMaxPdf(652.23)
# Add variables to be saved in ntuple.
tup = Tupling("Tupling")
tup.addCharge()
tup.addTime()
tup.addCompositeMass()


printAlgorithmSequence()
# Configure Hydra.
Hydra().EvtMax = 1000
#Hydra().AlgoSequence = seq
Hydra().Variables = Utils.addVectors( tup.getVariables() , sec.getVariables() )
Hydra().NThreads = -1
Hydra().TreeName = "d02kskk"
Hydra().OutputLocation = "d02kskk.root"
Hydra.run()