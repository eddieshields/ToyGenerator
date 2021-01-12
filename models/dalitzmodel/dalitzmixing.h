#ifndef TOYGEN_DALITZMIXING_H
#define TOYGEN_DALITZMIXING_H

#include "include/event.h"
#include "dalitzamplitude.h"
#include "msgservice.h"

namespace DalitzModel {

class DalitzMixing
{
public:
  DalitzMixing() {}
  DalitzMixing(DalitzAmplitude& amp) :
    m_amp( amp )
  {}
  ~DalitzMixing() {}

  const std::complex<double> A(Event& ev);
  const std::complex<double> A(const int& flav, const double& t, const double& mSq12, const double& mSq13);
  const std::complex<double> A(const int& flav, const double& t, const double& mSq12, const double& mSq13, const double& mSq23);

  const double ASq(Event& ev);
  const double ASq(const int& flav, const double& t, const double& mSq12, const double& mSq13);
  const double ASq(const int& flav, const double& t, const double& mSq12, const double& mSq13, const double& mSq23);


  const double               x() const { return m_x; }
  const double               y() const { return m_y; }
  const double               p() const { return m_p; }
  const double               q() const { return m_q; }
  const std::complex<double> z() const { return m_z; }

  void setX(const double& x) { m_x = x; m_z = std::complex<double>(m_x,m_y); }
  void setY(const double& y) { m_y = y; m_z = std::complex<double>(m_x,m_y); }
  void setP(const double& p) { m_p = p; }
  void setQ(const double& q) { m_q = q; }
  void printParameters()     { INFO("x = " << m_x << ", y = " << m_y << ", p = " << m_p << ", q = " << m_q); }

  DalitzAmplitude& amplitude() { return m_amp; }

private:
  const std::complex<double> gp(const double& t);
  const std::complex<double> gm(const double& t);

  double               m_x = {0.004};
  double               m_y = {0.006};
  double               m_q = {1.};
  double               m_p = {1.};
  std::complex<double> m_z = {0.004,0.006};

  DalitzAmplitude m_amp;
};

}

#endif
