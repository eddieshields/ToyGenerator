#include <cxxopts.hpp>

#include "clock.h"

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

#include "TFile.h"
#include "TTree.h"
#include "TH2.h"

TH2D* makeHistogram(TTree* tree, std::string var1, std::string var2)
{
  tree->Draw((var1+":"+var2+">>hist"+var1+var2).c_str());
  TH2D* hist = (TH2D*)gDirectory->Get(("hist"+var1+var2).c_str());
  return hist;
}

int main(int argc, char *argv[])
{
  
  cxxopts::Options options("ToyGenerator", "Program to generate D0->KsKK toys");
  options.add_options()
    ("f,file", "Decay file", cxxopts::value<std::string>()->default_value("options/kskk.dec"))
    ;
  auto parser = options.parse(argc, argv);

  EvtRandomEngine* eng = new EvtSimpleRandomEngine();;
  EvtAbsRadCorr* radCorrEngine = 0;
  std::list<EvtDecayBase*> extraModels;


  EvtGen myGenerator( "/afs/cern.ch/user/e/eshields/cernbox/ToyGenerator/options/kskk.dec" ,  "/afs/cern.ch/user/e/eshields/cernbox/ToyGenerator/EvtGen/share/evt.pdl" ,
                        eng, radCorrEngine, &extraModels );
   
  std::string mother( "D0" );
  EvtId id = EvtPDL::getId( mother );

  // Set up TTree.
  double qAB,qBC,qCA;
  TTree* t = new TTree();
  t->Branch("mSqAB",&qAB,"mSqAB/D");
  t->Branch("mSqBC",&qBC,"mSqBC/D");
  t->Branch("mSqAC",&qCA,"mSqAC/D");
  
  Clock::Start();
  int N = 1e7;
  int count = 1;
  do {
    EvtVector4R p_init( EvtPDL::getMass( id ), 0.0, 0.0, 0.0 );
    EvtParticle* root_part = EvtParticleFactory::particleFactory( id, p_init );
    root_part->setDiagonalSpinDensity();
    myGenerator.generateDecay( root_part );  
    int nDaug = root_part->getNDaug();
    if ( nDaug == 3 ) {
      EvtVector4R p0 = root_part->getDaug( 0 )->getP4Lab();
      EvtVector4R p1 = root_part->getDaug( 1 )->getP4Lab();
      EvtVector4R p2 = root_part->getDaug( 2 )->getP4Lab();
      qAB = ( p0 + p1 ).mass2();
      qBC = ( p1 + p2 ).mass2();
      qCA = ( p2 + p0 ).mass2();  
    }  
    root_part->deleteTree();
    t->Fill(); 
  } while ( count++ < N );
  Clock::Stop();
  Clock::Print("generate 1M events" );
  
  TH2D* hist0 = makeHistogram(t,"mSqAB","mSqBC");
  TH2D* hist1 = makeHistogram(t,"mSqAB","mSqAC");
  TH2D* hist2 = makeHistogram(t,"mSqAC","mSqBC");

  TFile* file = new TFile("/eos/lhcb/user/e/eshields/d02kskk-model/EvtGenAmplitudeD02KsKKTmp.root","RECREATE");
  file->cd();
  t->Write("d02kskk");
  hist0->Write("mSqABmSqBC");
  hist1->Write("mSqABmSqAC");
  hist2->Write("mSqACmSqBC");
  file->Close();

  return 0;
}