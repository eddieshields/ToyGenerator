#ifndef TOYGEN_HYDRA_H
#define TOYGEN_HYDRA_H

#include "event.h"
#include "algorithm.h"
#include "sequence.h"
#include "threads.h"
#include "clock.h"

#include <vector>
#include <map>

#include "TFile.h"
#include "TTree.h"

/*
TODO:
  Make similar to DaVinci. Configure everything within Hydra.
  Allow hydra to run toy generation sequence. Will include thread start and finish hear.
  Have TTree produced and saves.
  Allow plots if requested. Take classes from amplitude model. Start with 3 body. Can then be expanded to 4.
*/
class Hydra
{
public:
  Hydra() : m_runner( this ) {WelcomeMessage();}
  ~Hydra() {}

  // Struct for configuration.
  struct Configuration {
    int EvtMax = {1000};
    int NThreads = {32};
    std::string TreeName = {"DecayTree"};
    std::string TreeTitle = {"DecayTree"};
    std::string OutputLocation = {""};
    std::vector<std::string> Variables;
    Sequence AlgoSequence;
  };

  // Wrapper struct that is passed to threads for execution.
  struct Exec {
    Exec(Hydra* _base) : base( _base ) {}
    ~Exec() {}

    std::vector<Event> operator()(int thread)
    {
      return base->runSequence(thread);
    }
    Hydra* base;
  };

  Configuration m_configuration;
  Exec m_runner;

  Configuration& operator()() { return m_configuration; }
  void run();
  TTree* tree();

private:
  std::vector<Event> m_list;
  void addToList(Event ev) { m_list.push_back(ev); } 
  std::vector<Event> runSequence(int thread);
  unsigned int m_counter = {0};

  static void WelcomeMessage();
  static bool m_welcome;
};

#endif