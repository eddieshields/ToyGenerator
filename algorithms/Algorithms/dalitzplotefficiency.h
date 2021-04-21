#ifndef TOYGEN_DALILTZPLOTEFFICIENCY_H
#define TOYGEN_DALILTZPLOTEFFICIENCY_H

#include "event.h"
#include "algorithm.h"
#include "random.h"

#include "TH2.h"
#include "TFile.h"

class DalitzPlotEfficiency : public Algorithm
{
private:
  TH2*   m_acceptance;
  real_t m_max;

  std::string m_mSqAB;
  std::string m_mSqAC;

public:
  DalitzPlotEfficiency(std::string name, TH2* acceptance_histogram) :
    Algorithm(name),
    m_acceptance( acceptance_histogram ),
    m_mSqAB( "mSq12" ),
    m_mSqAC( "mSq13" )
  {
    m_max = m_acceptance->GetMaximum();
  };
  DalitzPlotEfficiency(std::string name, std::string path, std::string hist_name) :
    Algorithm(name),
    m_mSqAB( "mSq12" ),
    m_mSqAC( "mSq13" )
  {
    TFile* file = TFile::Open(path.c_str());
    file->cd();
    m_acceptance = (TH2*)file->Get(hist_name.c_str());
    if ( m_acceptance == nullptr ) {
      ERROR("Can't find histogram " << hist_name << " in file " << path);
    }
    m_acceptance->SetDirectory(0);
    file->Close();
    m_max = m_acceptance->GetMaximum();
  };
  ~DalitzPlotEfficiency() {};

  void SetDalitzAxis(std::string mSqAB, std::string mSqAC)
  {
    m_mSqAB = mSqAB;
    m_mSqAC = mSqAC;
  }

  virtual void operator() (Event& ev);
};

#endif