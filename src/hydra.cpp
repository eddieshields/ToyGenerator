#include "hydra.h"

void Hydra::run()
{
  // If threads are wanted set them to the maximum available.
  if ( m_configuration.NThreads == -1 || m_configuration.NThreads > std::thread::hardware_concurrency() ) {
    m_configuration.NThreads = std::thread::hardware_concurrency();
  }
  // Create temport directory to save files in.
  //boost::filesystem::path tmp = "tmp";
  //boost::filesystem::create_directory( tmp );

  // Run sequence.
  INFO("Will use " << m_configuration.NThreads << " threads");
  Clock::Start();
  Threads<Hydra::Exec> execute(m_runner,m_configuration.NThreads,m_configuration.EvtMax);
  execute();
  m_list = execute.list();
  Clock::Stop();
  Clock::Print("generate "+std::to_string(m_configuration.EvtMax)+" events");

  // Merge trees from temporary directory.
  merge_tree();

  // Delete tmp directory after merging files together.
  //boost::filesystem::remove_all( tmp );
}

std::vector<Event> Hydra::runSequence(int& thread)
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

  // Make this a critical process.
  temporary_tree(thread,list);
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

void Hydra::temporary_tree(int& thread, std::vector<Event>& list)
{
  TFile* file = new TFile(("tmp/tmp"+std::to_string(thread)+".root").c_str(),"RECREATE");
  file->cd();

  // Create new tree.
  TTree* tree = new TTree(m_configuration.TreeName.c_str(),m_configuration.TreeTitle.c_str());

  // Set branches.
  std::map<std::string,double> m_mapping;
  for (auto& var : m_configuration.Variables) {
    m_mapping[var] = 0.0;
    tree->Branch(var.c_str(),&m_mapping[var],(var+"/D").c_str());
  }

  // Fill tree.
  for(auto& ev : list) {
    if ( !ev.Accept ) continue;
    for (auto& var : m_configuration.Variables) {
      m_mapping[var] = ev[var];
    }
    tree->Fill();
  }

  // Save Tree.
  tree->Write();
  file->Close();
}

void Hydra::merge_tree()
{
  TChain* ch = new TChain(m_configuration.TreeName.c_str());
  for (int i = 0; i < m_configuration.NThreads; i++) {
    ch->Add(("tmp/tmp"+std::to_string(i)+".root").c_str());
  }
  ch->Merge(m_configuration.OutputLocation.c_str());
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