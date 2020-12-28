#include "event.h"
#include "generator.h"
#include "efficiency.h"
#include "amplitude.h"
#include "accept.h"
#include "sequence.h"
#include "d02k3pi.h"
#include "tupling.h"
#include "algorithm.h"
#include "clock.h"
#include "hydra.h"

#include <iostream>

int main()
{
  Hydra hy;
  hy.setDecay("D0 => K+ pi- pi+ pi-");
  
  Generator gen("Generator");
  D02K3Pi amp("Amplitude");
  Accept acc("Accept");
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

  hy().EvtMax = 10000;
  hy().TreeName = "d02k3pi";
  hy().AlgoSequence = flow;
  hy().NThreads = 32;
  hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root";
  hy().Variables = tup.getVariables();
  hy.run();
}