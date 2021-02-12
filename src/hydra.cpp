#include "hydra.h"

void Hydra::run()
{
  // If threads are wanted set them to the maximum available.
  if ( m_configuration.NThreads == -1 || m_configuration.NThreads > std::thread::hardware_concurrency() ) {
    m_configuration.NThreads = std::thread::hardware_concurrency();
  }
  // Run sequence.
  INFO("Requested to generate " << m_configuration.EvtMax << " Events");
  INFO("Will use " << m_configuration.NThreads << " threads");
  Clock::Start();
  DistributeTask execute(m_configuration.NThreads);
  // Create a task to be passed to the threadpool.
  auto func = [&](){return this->runSequence();};
  // Pass task to threadpool and get evets from return.
  m_list = execute(func);
  Clock::Stop();
  Clock::Print("generate "+std::to_string(m_configuration.EvtMax)+" events");

  // Put events into ttree.
  make_tree();
}

std::vector<Event> Hydra::runSequence()
{
  std::vector<Event> list;
  unsigned int counter = 0;
  while ( counter < m_configuration.EvtMax/m_configuration.NThreads ) {
    Event* ev = new Event();
    Algorithm* algo = nullptr;
    algo = m_configuration.AlgoSequence.head;
    while ( algo != nullptr ) {
      algo->operator()(*ev);
      algo = algo->next;
    }
    if ( ev->Accept ) {
      counter++;
      list.push_back( std::move(*ev) );
    }
    // Accepted events are saved in list, so events can be deleted.
    delete ev;
  }

  return list;
}

void Hydra::make_tree()
{
  Clock::Start();
  TFile* tfile = new TFile(m_configuration.OutputLocation.c_str(),"RECREATE");
  tfile->cd();

  TTree* tree = new TTree(m_configuration.TreeName.c_str(),m_configuration.TreeTitle.c_str());
  std::map<std::string,double> m_mapping;
  for (auto& var : m_configuration.Variables) {
    m_mapping[var] = 0.0;
    tree->Branch(var.c_str(),&m_mapping[var],(var+"/D").c_str());
  }

  for(auto& ev : m_list) {
    if ( !ev.Accept ) continue;
    for (auto& var : m_configuration.Variables) {
      m_mapping[var] = ev[var];
    }
    tree->Fill();
  }

  tree->Write();
  tfile->Close();
  Clock::Stop();
  Clock::Print("fill TTree with "+std::to_string(m_configuration.EvtMax)+" events");
  INFO("Tree saved to: " << m_configuration.OutputLocation);
}

bool Hydra::m_welcome = false;
void Hydra::WelcomeMessage()
{
  if ( !m_welcome ) {
  std::cout << "\033[1;31m**********************************************************\033[0m\n";
  std::cout << "\033[1;31m*                                                        *\033[0m\n";
  std::cout << "\033[1;31m*                    WELCOME TO HYDRA                    *\033[0m\n";
  std::cout << "\033[1;31m*                                                        *\033[0m\n";
  std::cout << "\033[1;31m*                                                        *\033[0m\n";
  std::cout << "\033[1;31m* Contact: edward.brendan.shields@cern.ch                *\033[0m\n";
  std::cout << "\033[1;31m*                                                        *\033[0m\n";
  std::cout << "\033[1;31m**********************************************************\033[0m\n" << std::endl;
  }
  m_welcome = true;
}