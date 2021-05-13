#include <cxxopts.hpp>

#include "clock.h"
#include "concurrentqueue.h"
#include "threadpool.h"
#include "progressbar.h"
#include "random.h"

#include "EvtGen/EvtGen.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenBase/EvtMTRandomEngine.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtSimpleRandomEngine.hh"
#include "EvtGenBase/EvtVector4R.hh"

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH2.h"


// Global queue.
moodycamel::ConcurrentQueue<std::map<std::string,double>> m_queue;

TH2D* makeHistogram(TTree* tree, std::string var1, std::string var2)
{
  tree->Draw((var1+":"+var2+">>hist"+var1+var2).c_str());
  TH2D* hist = (TH2D*)gDirectory->Get(("hist"+var1+var2).c_str());
  return hist;
}

void generateEvent(int N, EvtGen& myGenerator)
{
  std::string mother( "D0" );
  EvtId id = EvtPDL::getId( mother );

  int count = 1;
  double qAB,qBC,qCA,amp;
  do {
    std::map<std::string,double> m_vars;
    EvtVector4R p_init( EvtPDL::getMass( id ), 0.0, 0.0, 0.0 );
    EvtParticle* root_part = EvtParticleFactory::particleFactory( id, p_init );
    root_part->setDiagonalSpinDensity();
    myGenerator.generateDecay( root_part );  
    int nDaug = root_part->getNDaug();
    if ( nDaug == 3 ) {
      EvtVector4R p0 = root_part->getDaug( 0 )->getP4Lab();
      EvtVector4R p1 = root_part->getDaug( 1 )->getP4Lab();
      EvtVector4R p2 = root_part->getDaug( 2 )->getP4Lab();

      // Add variables.
      m_vars.insert( std::pair<std::string,double>{ "KS_PX" , p0.get(0) } );
      m_vars.insert( std::pair<std::string,double>{ "KS_PY" , p0.get(1) } );
      m_vars.insert( std::pair<std::string,double>{ "KS_PZ" , p0.get(2) } );
      m_vars.insert( std::pair<std::string,double>{ "KS_E"  , p0.get(3) } );

      m_vars.insert( std::pair<std::string,double>{ "Kp_PX" , p1.get(0) } );
      m_vars.insert( std::pair<std::string,double>{ "Kp_PY" , p1.get(1) } );
      m_vars.insert( std::pair<std::string,double>{ "Kp_PZ" , p1.get(2) } );
      m_vars.insert( std::pair<std::string,double>{ "Kp_E"  , p1.get(3) } );

      m_vars.insert( std::pair<std::string,double>{ "Km_PX" , p2.get(0) } );
      m_vars.insert( std::pair<std::string,double>{ "Km_PY" , p2.get(1) } );
      m_vars.insert( std::pair<std::string,double>{ "Km_PZ" , p2.get(2) } );
      m_vars.insert( std::pair<std::string,double>{ "Km_E"  , p2.get(3) } );

      qAB = ( p0 + p1 ).mass2();
      m_vars.insert( std::pair<std::string,double>{ "mSqAB"  , qAB } );
      qBC = ( p1 + p2 ).mass2();
      m_vars.insert( std::pair<std::string,double>{ "mSqBC"  , qBC } );
      qCA = ( p2 + p0 ).mass2();  
      m_vars.insert( std::pair<std::string,double>{ "mSqAC"  , qCA } );
      amp = *root_part->decayProb();
      m_vars.insert( std::pair<std::string,double>{ "ASq"  , amp } );
    }  
    m_queue.enqueue( m_vars );

    root_part->deleteTree();

  } while ( count++ < N );

  return;
}

// Wrapper class for thread safe number generator.
class EvtSimpleThreadedRandomEngine : public EvtRandomEngine
{
public:

  EvtSimpleThreadedRandomEngine(int seed)
  {
    Random::setSeed( seed );
  }
  ~EvtSimpleThreadedRandomEngine() {}

  double random() override
  {
    return Random::flat();
  }

};

int main(int argc, char *argv[])
{
  
  cxxopts::Options options("ToyGenerator", "Program to generate D0->KsKK toys");
  options.add_options()
    ("f,file", "Decay file", cxxopts::value<std::string>()->default_value("options/kskk.dec"))
    ("s,seed", "Random seed", cxxopts::value<int>()->default_value("1"))
    ;
  auto parser = options.parse(argc, argv);

  EvtRandomEngine* eng = new EvtSimpleThreadedRandomEngine(parser["seed"].as<int>());
  EvtAbsRadCorr* radCorrEngine = 0;
  std::list<EvtDecayBase*> extraModels;

  EvtGen myGenerator( "options/kskk.dec" ,  "EvtGen/share/evt.pdl" ,
                        eng, radCorrEngine, &extraModels );
  TFile* file = new TFile(("EvtGenAmplitudeD02KsKK_"+std::to_string(parser["seed"].as<int>())+".root").c_str(),"RECREATE");
  file->cd();

  // Set up TTree.
  TTree* t = new TTree();
  std::vector<std::string> vars = {"KS_PX","KS_PY","KS_PZ","KS_E",
                      "Kp_PX","Kp_PY","Kp_PZ","Kp_E",
                      "Km_PX","Km_PY","Km_PZ","Km_E",
                      "KS_PX","KS_PY","KS_PZ","KS_E",
                      "ASq","mSqAB","mSqAC","mSqBC"};
  std::map<std::string,double> v_store;
  for (auto& v : vars) {
    v_store.insert( std::pair<std::string,double>{v,0.} );
    t->Branch(v.c_str(),&v_store[v],(v+"/D").c_str());
  }

  int N = 1e6;

  //ThreadPool pool;
  //int nthreads = std::thread::hardware_concurrency();
  //for (int i = 0; i < nthreads; i++) {
  //  pool.submit( generateEvent , N/nthreads , myGenerator );
  //}

  
  int count = 0;
  bool success;
  std::map<std::string,double> ev;
  ProgressBar pb( N );
  Clock::Start();
  //do {
  //  success = m_queue.try_dequeue( ev );
  //  if ( !success ) continue;
  //  for (auto& v : vars) {
  //    v_store[v] = ev[v];
  //  }
  //  t->Fill();
  //  ++pb;
  //} while ( count++ < N );
  std::string mother( "D0" );
  EvtId id = EvtPDL::getId( mother );


  double qAB,qBC,qCA,amp;
  do {
    std::map<std::string,double> m_vars;
    EvtVector4R p_init( EvtPDL::getMass( id ), 0.0, 0.0, 0.0 );
    EvtParticle* root_part = EvtParticleFactory::particleFactory( id, p_init );
    root_part->setDiagonalSpinDensity();
    myGenerator.generateDecay( root_part );  
    int nDaug = root_part->getNDaug();
    if ( nDaug == 3 ) {
      EvtVector4R p0 = root_part->getDaug( 0 )->getP4Lab();
      EvtVector4R p1 = root_part->getDaug( 1 )->getP4Lab();
      EvtVector4R p2 = root_part->getDaug( 2 )->getP4Lab();

      // Add variables.
      m_vars.insert( std::pair<std::string,double>{ "KS_PX" , p0.get(0) } );
      m_vars.insert( std::pair<std::string,double>{ "KS_PY" , p0.get(1) } );
      m_vars.insert( std::pair<std::string,double>{ "KS_PZ" , p0.get(2) } );
      m_vars.insert( std::pair<std::string,double>{ "KS_E"  , p0.get(3) } );

      m_vars.insert( std::pair<std::string,double>{ "Kp_PX" , p1.get(0) } );
      m_vars.insert( std::pair<std::string,double>{ "Kp_PY" , p1.get(1) } );
      m_vars.insert( std::pair<std::string,double>{ "Kp_PZ" , p1.get(2) } );
      m_vars.insert( std::pair<std::string,double>{ "Kp_E"  , p1.get(3) } );

      m_vars.insert( std::pair<std::string,double>{ "Km_PX" , p2.get(0) } );
      m_vars.insert( std::pair<std::string,double>{ "Km_PY" , p2.get(1) } );
      m_vars.insert( std::pair<std::string,double>{ "Km_PZ" , p2.get(2) } );
      m_vars.insert( std::pair<std::string,double>{ "Km_E"  , p2.get(3) } );

      //int id = root_part->getPDGId();
      //int pid = root_part->getId().isConjugate( root_part->getId() ) ? -id : id;
      //m_vars.insert( std::pair<std::string,double>{ "pid" , (double)( pid ) } );
      //std::cout  << "pid = " << id << std::endl;

      qAB = ( p0 + p1 ).mass2();
      m_vars.insert( std::pair<std::string,double>{ "mSqAB"  , qAB } );
      qBC = ( p1 + p2 ).mass2();
      m_vars.insert( std::pair<std::string,double>{ "mSqBC"  , qBC } );
      qCA = ( p2 + p0 ).mass2();  
      m_vars.insert( std::pair<std::string,double>{ "mSqAC"  , qCA } );
      amp = *root_part->decayProb();
      m_vars.insert( std::pair<std::string,double>{ "ASq"  , amp } );
    }  
    //m_queue.enqueue( m_vars );

    root_part->deleteTree();

    //success = m_queue.try_dequeue( ev );
    //if ( !success ) continue;
    for (auto& v : m_vars) {
      v_store[v.first] = v.second;
    }
    t->Fill();
    ++pb;
  } while ( count++ < N );
  Clock::Stop();
  Clock::Print("generate 1M events" );
  
  //TH2D* hist0 = makeHistogram(t,"mSqAB","mSqBC");
  //TH2D* hist1 = makeHistogram(t,"mSqAB","mSqAC");
  //TH2D* hist2 = makeHistogram(t,"mSqAC","mSqBC");

  t->Write("d02kskk");
  //hist0->Write("mSqABmSqBC");
  //hist1->Write("mSqABmSqAC");
  //hist2->Write("mSqACmSqBC");
  file->Close();
  std::cout << "Saved to: " << "EvtGenAmplitudeD02KsKK_"+std::to_string(parser["seed"].as<int>())+".root" << std::endl;
  return 0;
}
