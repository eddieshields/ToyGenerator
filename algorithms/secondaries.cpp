#include "secondaries.h"

void Secondaries::operator()(Event& ev)
{
  if ( !ev.Accept ) return;
  double t_reco = ev.mother().time();
  if ( fraction( t_reco ) > gRandom->Rndm() ) {
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

void Secondaries::LoadFraction(std::string frac_file, std::string frac_obj)
{
  TFile* frac_tfile = TFile::Open(frac_file.c_str());
  frac_tfile->cd();
  frac_tfile->GetObject(frac_obj.c_str(),m_fraction);
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

const double Secondaries::fraction(const double& t_reco)
{
  return m_fraction->Eval( t_reco );
}


const double Secondaries::true_time(const double& t_reco)
{
  int bin;
  bin = m_hist->GetXaxis()->FindBin( t_reco ) - 1;
  if ( bin < m_hists.size() ) {
    if ( m_hists[bin]->GetEntries() ) {
      double t_true;
      t_true = m_hists[bin]->GetRandom();
      return t_true;
    }
  }
  return t_reco;
}