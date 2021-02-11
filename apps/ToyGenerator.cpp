/*
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
*/
// DalitzModel.
#include "relbreitwigner.h"
#include "flatte.h"
#include "parameter.h"
#include "configfile.h"
#include "configureamplitude.h"
#include "dalitzplot.h"
#include "msgservice.h"
#include "clock.h"

// ROOT.
#include "TH2.h"
#include "TAxis.h"
#include "TCanvas.h"

int main()
{
  /*
  Hydra hy;
  hy.setDecay("D0 => KS0 K+ K-");
  
  Generator gen("Generator");
  Decay3Body amp("Amplitude","cfg/belle2010.cfg");
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
  hy().OutputLocation = "/Users/eddieshields/Documents/LHCb/ToyGenerator/build/tmp/output.root";
  hy().Variables = tup.getVariables();
  hy.run();
  */
  DalitzModel::Coefficient::Coords = DalitzModel::Coordinates::Polar;
  DalitzModel::ConfigureAmplitude configure("cfg/babar2010.cfg");
  DalitzModel::Amplitude amp = configure();
  //DalitzModel::LineShape::Flatte::SetParameterisation( "BaBar2010" );
  TH2D* hist = new TH2D("hist","hist",1000,amp.ps().mSq12min(),amp.ps().mSq12max(),1000,amp.ps().mSq13min(),amp.ps().mSq13max());

  PRINT( amp );
  double mSq12, mSq13, mSq23;
  Clock::Start();
  for (int i = 1; i < hist->GetNbinsX() + 1; i++) {
    for (int j = 1; j < hist->GetNbinsY() + 1; j++) {
      mSq12 = hist->GetXaxis()->GetBinCenter(i);
      mSq13 = hist->GetYaxis()->GetBinCenter(j);
      double A = amp.AdirSq("a00_980",mSq12,mSq13);
      hist->SetBinContent(i,j,A);
    }
  }



  Clock::Stop();
  Clock::Print("fill histogram with threading");

  DalitzModel::DalitzPlot dp( amp.ps() );

  TCanvas* canv = dp.plot( hist );
  canv->Print("figs/dalitzplot.png");

  canv = dp.plotProjection( hist , "x" );
  canv->Print("figs/dalitzplot_x.png");

  canv = dp.plotProjection( hist , "y" );
  canv->Print("figs/dalitzplot_y.png");
  
  return 0;
}