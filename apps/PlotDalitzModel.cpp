// DalitzModel.
#include "relbreitwigner.h"
#include "flatte.h"
#include "parameter.h"
#include "configfile.h"
#include "configureamplitude.h"
#include "dalitzplot.h"
#include "msgservice.h"
#include "clock.h"
#include "types.h"

// ROOT.
#include "TH2.h"
#include "TAxis.h"
#include "TCanvas.h"

#include <cxxopts.hpp>

int main(int argc, char *argv[])
{
  cxxopts::Options options("ToyGenerator", "Program to generate D0->KsKK toys");
  options.add_options()
    ("m,model", "Model", cxxopts::value<std::string>()->default_value("belle2010"))
    ;
  auto parser = options.parse(argc, argv);

  DalitzModel::Coefficient::CoordinatesSystem = DalitzModel::Coordinates::Rectangular;
  DalitzModel::ConfigureAmplitude configure("cfg/"+parser["model"].as<std::string>()+".cfg");
  DalitzModel::Amplitude amp = configure();
  //DalitzModel::LineShape::Flatte::SetParameterisation( "BaBar2010" );
  TH2D* hist = new TH2D("hist","hist",1000,amp.ps().mSq12min(),amp.ps().mSq12max(),1000,amp.ps().mSq13min(),amp.ps().mSq13max());

  PRINT( amp );
  real_t mSq12, mSq13;
  Clock::Start();
  for (int i = 1; i < hist->GetNbinsX() + 1; i++) {
    for (int j = 1; j < hist->GetNbinsY() + 1; j++) {
      mSq12 = hist->GetXaxis()->GetBinCenter(i);
      mSq13 = hist->GetYaxis()->GetBinCenter(j);
      real_t A = amp.ASq(mSq12,mSq13);
      hist->SetBinContent(i,j,A);
    }
  }

  Clock::Stop();
  Clock::Print("fill histogram");

  DalitzModel::DalitzPlot dp( amp.ps() );

  TCanvas* canv = dp.plot( hist );
  canv->Print(("figs/dalitzplot_"+parser["model"].as<std::string>()+".png").c_str());

  canv = dp.plotProjection( hist , "x" );
  canv->Print(("figs/dalitzplot_"+parser["model"].as<std::string>()+"_x.png").c_str());

  canv = dp.plotProjection( hist , "y" );
  canv->Print(("figs/dalitzplot_"+parser["model"].as<std::string>()+"_y.png").c_str());
  
  return 0;
}