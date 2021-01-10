#include "hydra.h"

void Hydra::run()
{
  INFO("Will use " << m_configuration.NThreads << " threads");
  Clock::Start();
  Threads<Hydra::Exec> execute(m_runner,m_configuration.NThreads,m_configuration.EvtMax);
  execute();
  m_list = execute.list();
  Clock::Stop();
  Clock::Print("generate "+std::to_string(m_configuration.EvtMax)+" events");

  Clock::Start();
  TTree* ttree = tree();
  Clock::Stop();
  Clock::Print("fill tree with "+std::to_string(ttree->GetEntries())+" events");
  ttree->Print();


  TFile* file = new TFile(m_configuration.OutputLocation.c_str(),"RECREATE");
  file->cd();
  ttree->Write();
  file->Close();
  INFO("Tree saved to: " << m_configuration.OutputLocation);
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

TTree* Hydra::tree()
{
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

  return tree;
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