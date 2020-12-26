#include "event.h"
#include "generator.h"
#include "efficiency.h"
#include "amplitude.h"
#include "sequence.h"
#include "algorithm.h"
#include "hydra.h"
#include "linkedlist.h"

#include <iostream>

int main()
{
  Hydra hy;

  Generator gen("Generator",1.9,0.4,0.4,0.5);
  Efficiency eff("Efficiency");
  Efficiency eff1("Efficiency1");
  Efficiency eff2("Efficiency2");
  Efficiency eff3("Efficiency3");
  Amplitude amp("Amplitude");

  Sequence flow;
  flow.addAlgorithm(gen);
  flow.addAlgorithm(eff);
  flow.addAlgorithm(eff1);
  flow.addAlgorithm(eff2);
  flow.addAlgorithm(eff3);
  flow.addAlgorithm(amp);
  flow.printAlgorithmSequence();

  hy().EvtMax = 1000;
  hy().TreeName = "d02kshh";
  hy().AlgoSequence = flow;
  hy().OutputLocation = "";
  
  hy.run();

  TTree* tree = hy.tree();
  tree->Print();
}