#ifndef TOYGEN_SECONDARIES_H
#define TOYGEN_SECONDARIES_H

#include "event.h"
#include "algorithm.h"
#include "msgservice.h"

#include <string>
#include <vector>

// ROOT.
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TFormula.h"
#include "TRandom.h"

class Secondaries : public Algorithm
{
public:
  Secondaries(std::string name) :
    Algorithm( name )
  {}
  ~Secondaries() {}

  void LoadHistogram(std::string hist_file, std::string hist_obj);
  void LoadFraction (std::string frac_file, std::string frac_obj);

  virtual void operator() (Event& ev);

  const double fraction (const double& t_reco);
  const double true_time(const double& t_reco);

  std::vector<std::string> getVariables() { return std::vector<std::string>{"isTruePrompt"}; }
private:
  void m_construct_hist_vector();
  TF1* m_fraction;
  TH2D* m_hist;
  std::vector<TH1D*> m_hists;
};

#endif