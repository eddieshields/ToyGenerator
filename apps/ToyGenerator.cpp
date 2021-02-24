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

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
  cxxopts::Options options("ToyGenerator", "Program to generate D0->KsKK toys");
  options.add_options()
    ("m,model", "Model", cxxopts::value<std::string>()->default_value("belle2010"))
    ;
  auto parser = options.parse(argc, argv);

  Hydra hy;
  hy.setDecay("D0 => KS0 K+ K-");
  
  Generator gen("Generator");
  Decay3Body amp("Amplitude","cfg/"+parser["model"].as<std::string>()+".cfg");
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
  hy().OutputLocation = "d02kskk.root";
  hy().Variables = tup.getVariables();
  hy.run();
}