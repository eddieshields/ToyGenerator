#include "hydra.h"

void Hydra::runSequence()
{
  m_counter = 0;

  while ( m_counter < m_configuration.EvtMax ) {
    Event* ev = new Event();
    Algorithm* algo = m_configuration.AlgoSequence.head;
    while ( algo != nullptr ) {
      algo->operator()(*ev);
      algo = algo->next;
    }
    if ( ev->Accept ) m_counter++;
    addToList(*ev);
  }
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