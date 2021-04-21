#ifndef TOYGEN_DECAYTIMEEFFICIENCY_H
#define TOYGEN_DECAYTIMEEFFICIENCY_H

#include "event.h"
#include "algorithm.h"
#include "random.h"

#include "TH1.h"

class DecayTimeEfficiency : public Algorithm
{
private:
  TH1*   m_acceptance;
  real_t m_max;
public:
  DecayTimeEfficiency(std::string name, TH1* acceptance_histogram) :
    Algorithm(name),
    m_acceptance( acceptance_histogram ) 
  {
    m_max = m_acceptance->GetMaximum();
  };
  DalitzPlotEfficiency(std::string name, std::string path, std::string hist_name) :
    Algorithm(name)
  {
    TFile* file = TFile::Open(path.c_str());
    file->cd();
    m_acceptance = (TH1*)file->Get(hist_name.c_str());
    if ( m_acceptance == nullptr ) {
      ERROR("Can't find histogram " << hist_name << " in file " << path);
    }
    m_acceptance->SetDirectory(0);
    file->Close();
    m_max = m_acceptance->GetMaximum();
  };
  ~DecayTimeEfficiency() {};

  virtual void operator() (Event& ev);
};

#endif