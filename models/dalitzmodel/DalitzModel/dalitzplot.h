#ifndef D02KSKK_DALITZPLOT_H
#define D02KSKK_DALITZPLOT_H

// Package.
#include "phasespace.h"
#include "amplitude.h"
#include "types.h"
#include "types.h"

// SL.
#include <iostream>
#include <string>
#include <vector>

// ROOT.
#include "TCanvas.h"
#include "TH2.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TText.h"
#include "TPaveText.h"


namespace DalitzModel {

/** @brief DalitzPlot class used to plots and projections of a Dalitz Plot.
 * 
 * Given the masses of the of the particles invloved in the decay, this class
 * provides methods for plotting an amplitude models dalitz plot and projections
 * of it. Further methods can be used to configure the plots.
 * 
 * @author Edward Shields
 * @date   05/11/2020
 */
class DalitzPlot
{
public:
  /** Constructor. */
  DalitzPlot() = default;
  DalitzPlot(PhaseSpace& ps) :
    m_ps( ps )
  {
    lhcbStyle();
  }
  /** Constructor. */
  DalitzPlot(const real_t& mMother, const real_t& m1, const real_t& m2, const real_t& m3) :
    m_ps( mMother, m1, m2, m3 )
  {
    lhcbStyle();
  }
  /** Destructor. */
  virtual ~DalitzPlot() {};

  /** Returns canvas with Dalitz plot. */
  TCanvas* plot(TH2* his);
  /** Returns projection of Dalitz plot. */
  TCanvas* plotProjection(TH2* his, std::string var = "x");
  /** Returns projections of multiple dalitz plots. Takes vector of histograms as input. */
  TCanvas* plotProjection(std::vector<TH2*> hiss, std::string var = "x");

  /** Set unit of variables. */
  void setUnit(std::string unit) { m_unit = unit; }
  /** Set X-axis title. */
  void setXtitle(std::string xaxis) { m_xaxis = xaxis; }
  /** Set Y-axis title. */
  void setYtitle(std::string yaxis) { m_yaxis = yaxis; }

  void lhcbStyle();

private:
  void decorate(TH2* his);
  void setBoundaryOptions(TGraph* boundary);
  TGraph* setBoundary(const int& boundary_points = 1000);

  std::string m_unit = {std::string("MeV/#it{c}^{2}")};
  std::string m_xaxis = {std::string("m^{2}(K_{S}^{0}K^{+})")};
  std::string m_yaxis = {std::string("m^{2}(K_{S}^{0}K^{-})")};

  PhaseSpace m_ps;
};

} // namespace DalitzModel

#endif