#include "hydra.h"

void Hydra::run()
{
  Clock::Start();
  Threads execute(m_runner,m_configuration.NThreads);
  Clock::Stop();
  Clock::Print("generate "+std::to_string(m_configuration.EvtMax)+" events");
}

void Hydra::runSequence()
{
  unsigned int counter = 0;

  while ( counter < m_configuration.EvtMax/m_configuration.NThreads ) {
    Event* ev = new Event();
    Algorithm* algo = m_configuration.AlgoSequence.head;
    while ( algo != nullptr ) {
      algo->operator()(*ev);
      algo = algo->next;
    }
    if ( ev->Accept ) counter++;
  }
  return;
}

TTree* Hydra::tree()
{
  TTree* tree = new TTree(m_configuration.TreeName.c_str(),m_configuration.TreeTitle.c_str());
  double pdf;
  tree->Branch("pdf",&pdf);

  for(auto& ev : m_list) {
    if ( !ev.Accept ) continue;
    pdf = ev.pdf;
    tree->Fill();
  }

  return tree;
}

bool Hydra::m_welcome = false;
void Hydra::WelcomeMessage()
{
  if ( !m_welcome ) {
  std::cout << "\033[1;31m**********************************************************\033[0m\n" << std::endl;
  //std::cout << "\033[1;31m*                                                        *\033[0m\n" << std::endl;
  std::cout << "\033[1;31m*                    WELCOME TO HYDRA                    *\033[0m\n" << std::endl;
  std::cout << "\033[1;31m*                                                        *\033[0m\n" << std::endl;
  std::cout << "\033[1;31m* Contact: edward.brendan.shields@cern.ch                *\033[0m\n" << std::endl;
  std::cout << "\033[1;31m**********************************************************\033[0m\n" << std::endl;
  }
  m_welcome = true;
}