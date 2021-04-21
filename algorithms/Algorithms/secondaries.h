#ifndef TOYGEN_SECONDARIES_H
#define TOYGEN_SECONDARIES_H

#include "event.h"
#include "algorithm.h"
#include "correlationutils.h"
#include "msgservice.h"
#include "random.h"
#include "types.h"

#include <string>
#include <vector>

// ROOT.
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TFormula.h"
#include "TFitResult.h"

class Secondaries : public Algorithm
{
public:
  Secondaries(std::string name) :
    Algorithm( name )
  {}
  ~Secondaries() {}

  void LoadHistogram(std::string hist_file, std::string hist_obj);
  void LoadFraction (std::string frac_file, std::string frac_obj, std::string res_obj = "");

  virtual void operator() (Event& ev);

  const real_t fraction (const real_t& t_reco);
  const real_t true_time(const real_t& t_reco);

  std::vector<std::string> getVariables() { return std::vector<std::string>{"isTruePrompt"}; }
private:
  void m_construct_hist_vector();
  TF1* m_fraction = {nullptr};
  TH2D* m_hist    = {nullptr};
  std::vector<TH1D*> m_hists;

  TFitResult* m_result = {nullptr};
};

#endif