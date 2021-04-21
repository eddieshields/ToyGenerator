#include "event.h"
#include "generator.h"
#include "efficiency.h"
#include "amplitude.h"
#include "accept.h"
#include "sequence.h"
#include "d02k3pi.h"
#include "decay3body.h"
#include "decay3bodymixing.h"
#include "tupling.h"
#include "algorithm.h"
#include "clock.h"
#include "hydra.h"
#include "random.h"

#include <iostream>

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
  cxxopts::Options options("ToyGenerator", "Program to generate D0->KsKK toys");
  options.add_options()
    ("m,model", "Model", cxxopts::value<std::string>()->default_value("belle2010"))
    ("s,seed", "Random seed", cxxopts::value<int>()->default_value("1"))
    ;
  auto parser = options.parse(argc, argv);

  Hydra hy;
  hy.setDecay("D0 => K_S0 K+ K-");
  
  Random::setSeed( parser["seed"].as<int>() );
  
  Generator gen("Generator");
  Decay3BodyMixing amp("Amplitude","cfg/"+parser["model"].as<std::string>()+".cfg");
  Accept acc("Accept");
  acc.setMaxPdf(645);
  Tupling tup("Tupling");
  tup.addMass();
  tup.addCompositeMass();
  tup.addCharge();
  tup.addTime();
  tup.addPID();
  tup.printParams();
  
  Sequence flow;
  flow.addAlgorithm(gen);
  flow.addAlgorithm(amp);
  flow.addAlgorithm(acc);
  flow.addAlgorithm(tup);
  flow.printAlgorithmSequence();

  hy().EvtMax = 1000000;
  hy().TreeName = "d02kskk";
  hy().AlgoSequence = flow;
  hy().NThreads = -1;
  hy().OutputLocation = "d02kskk.root";
  hy().Variables = tup.getVariables();
  hy.run();
}
