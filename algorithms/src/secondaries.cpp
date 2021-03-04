#include "secondaries.h"

void Secondaries::operator()(Event& ev)
{
  if ( !ev.Accept ) return;
  real_t t_reco = ev.mother().time();
  if ( fraction( t_reco ) > Random::Rnd() ) {
    ev.mother().truetime() = true_time( t_reco );
    ev["isTruePrompt"] = 0;
  } else {
    ev["isTruePrompt"] = 1;
  }
  return;
}

void Secondaries::LoadHistogram(std::string hist_file, std::string hist_obj)
{
  TFile* hist_tfile = TFile::Open(hist_file.c_str());
  hist_tfile->cd();
  hist_tfile->GetObject(hist_obj.c_str(),m_hist);
  m_hist->SetDirectory(0);
  hist_tfile->Close();

  m_construct_hist_vector();
  if ( m_hist != nullptr ) INFO("Found histogram!");
  return;
}

void Secondaries::LoadFraction(std::string frac_file, std::string frac_obj, std::string res_object)
{
  TFile* frac_tfile = TFile::Open(frac_file.c_str());
  frac_tfile->cd();
  frac_tfile->GetObject(frac_obj.c_str(),m_fraction);

  if ( res_object != "" ) {
    frac_tfile->GetObject(res_object.c_str(),m_result);
    INFO("Varying fraction parameters");
    m_fraction = CorrelationUtils::VaryFunction(m_fraction,m_result);
  }
  // Do an evaluation to initialise TF1 outside the threaded environment.
  m_fraction->Eval(1.);
  frac_tfile->Close();

  if ( m_fraction != nullptr ) INFO("Found fraction!");
  return;
}

void Secondaries::m_construct_hist_vector()
{
  for (int i = 1; i < m_hist->GetNbinsY(); i++) {
    m_hists.push_back( m_hist->ProjectionY(std::to_string(i).c_str(),i,i+1) );
  }
}

const real_t Secondaries::fraction(const real_t& t_reco)
{
  return m_fraction->Eval( t_reco );
}


const real_t Secondaries::true_time(const real_t& t_reco)
{
  int bin;
  bin = m_hist->GetXaxis()->FindBin( t_reco ) - 1;
  if ( bin < m_hists.size() ) {
    if ( m_hists[bin]->GetEntries() ) {
      real_t t_true;
      t_true = m_hists[bin]->GetRandom();
      return t_true;
    }
  }
  return t_reco;
}