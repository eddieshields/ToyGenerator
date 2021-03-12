#ifndef TOYGEN_HYDRA_H
#define TOYGEN_HYDRA_H

#include "event.h"
#include "algorithm.h"
#include "sequence.h"
#include "distributetask.h"
#include "descriptor.h"
#include "clock.h"
#include "progressbar.h"

#include <vector>
#include <map>
#include <thread>
#include <queue>
#include <mutex>

// Dirty fix, should try fix in compilation instead.
//#define BOOST_NO_CXX11_SCOPED_ENUMS
//#include <boost/filesystem.hpp>
//#undef BOOST_NO_CXX11_SCOPED_ENUMS

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"


// Struct for configuration.
struct Configuration {
  Configuration()  {}
  ~Configuration() {}
  int                      EvtMax         = {1000};
  int                      NThreads       = {1};
  std::string              TreeName       = {"DecayTree"};
  std::string              TreeTitle      = {"DecayTree"};
  std::string              OutputLocation = {""};
  std::vector<std::string> Variables;
  Sequence                 AlgoSequence;
};


/** @brief Hydra is the central class used to configure and generate toys.
 * 
 * Hydra is the central object in the package the used to configure settings as well as performs the 
 * execution of a series of algorithms. 
 * 
 * Options are called with the () operator. I.e. to set the number of events do Hydra().EvtMax = 1000.
 * Once all the options are set call Hydra.run() to run the sequence loop and generate an output.
 * 
 * @author Edward Shields
 * @date   07/01/2021
 */
class Hydra
{
public:
  Hydra() {WelcomeMessage();}
  virtual ~Hydra() {}

  Configuration m_configuration;
  Configuration& operator()() { return m_configuration; }
  void runSequence();
  void run();
  void make_tree();
  void fill_tree();
  void addToList(std::vector<Event> tmp) { m_list.insert( m_list.end(), tmp.begin(), tmp.end() ); }
  void setDecay(std::string decay) { gDescriptor(decay); }

  static void SetDecay(std::string decay) { gDescriptor(decay); }
  static void WelcomeMessage();
  static bool m_welcome;
private:
  std::vector<Event> m_list;
  void addToList(Event ev) { m_list.push_back(ev); } 
  unsigned int m_counter = {0};

  std::map<std::thread::id,std::queue<Event>> m_queue;
  std::mutex                                  m_mutex;
};

#endif