#include "event.h"
#include "generator.h"
#include "efficiency.h"
#include "amplitude.h"
#include "accept.h"
#include "sequence.h"
#include "tupling.h"
#include "algorithm.h"
#include "clock.h"
#include "hydra.h"

#include <iostream>

int main()
{
  Hydra hy;

  Generator gen("Generator",1.9,0.4,0.4,0.5);
  Efficiency eff("Efficiency");
  Amplitude amp("Amplitude");
  Accept acc("Accept");
  Tupling tup("Tupling");

  Sequence flow;
  flow.addAlgorithm(gen);
  flow.addAlgorithm(eff);
  flow.addAlgorithm(amp);
  flow.addAlgorithm(acc);
  flow.addAlgorithm(tup);
  flow.printAlgorithmSequence();

  hy().EvtMax = 100000;
  hy().TreeName = "d02kshh";
  hy().AlgoSequence = flow;
  hy().OutputLocation = "";
  hy().NThreads = 1;
  hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root";
  hy().Variables = {"mSq12","mSq13","mSq23"};
  hy.run();

  TTree* tree = hy.tree();
  tree->Print();
}