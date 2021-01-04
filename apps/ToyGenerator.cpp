#include "event.h"
#include "generator.h"
#include "efficiency.h"
#include "amplitude.h"
#include "accept.h"
#include "sequence.h"
#include "d02k3pi.h"
#include "decay3body.h"
#include "tupling.h"
#include "algorithm.h"
#include "clock.h"
#include "hydra.h"

#include <iostream>

int main()
{
  Hydra hy;
  hy.setDecay("D0 => KS0 K+ K-");
  
  Generator gen("Generator");
  Decay3Body amp("Amplitude","cfg/belle2010.cfg");
  Accept acc("Accept");
  acc.setMaxPdf(624);
  Tupling tup("Tupling");
  tup.addMass();
  tup.addCompositeMass();
  tup.printParams();

  Sequence flow;
  flow.addAlgorithm(gen);
  flow.addAlgorithm(amp);
  flow.addAlgorithm(acc);
  flow.addAlgorithm(tup);
  flow.printAlgorithmSequence();

  hy().EvtMax = 100000;
  hy().TreeName = "d02kshh";
  hy().AlgoSequence = flow;
  hy().NThreads = 1;
  hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root";
  hy().Variables = tup.getVariables();
  hy.run();
}