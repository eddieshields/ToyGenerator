#ifndef TOYGEN_DECAY3BODYMIXING_H
#define TOYGEN_DECAY3BODYMIXING_H

#include "event.h"
#include "algorithm.h"
#include "configureamplitude.h"
#include "amplitude.h"

#include <complex>

class Decay3BodyMixing : public Algorithm
{
public:
  Decay3BodyMixing(std::string name, std::string cfgfile) :
    Algorithm( name )
  {
    DalitzModel::ConfigureAmplitude configure( cfgfile );
    m_amp = configure();
  } 
  ~Decay3BodyMixing() {}

  DalitzModel::Amplitude& amp() { return m_amp; }

  // Getters.
  const double               x() const { return m_x; }
  const double               y() const { return m_y; }
  const double               p() const { return m_p; }
  const double               q() const { return m_q; }
  const std::complex<double> z() const { return m_z; }

  // Setters.
  void setX(double x) { m_x = x; m_z = std::complex<double>(m_x,m_y); }
  void setY(double y) { m_y = y; m_z = std::complex<double>(m_x,m_y); }
  void setP(double p) { m_p = p; }
  void setQ(double q) { m_q = q; }

  // Operator.
  virtual void operator() (Event& ev);
private:
  DalitzModel::Amplitude m_amp;

  // Mixing parameters.
  double m_x = {0.004};
  double m_y = {0.006};
  double m_p = {1};
  double m_q = {1};
  std::complex<double> m_z = {std::complex<double>(0.004,0.006)};

  // Mixing functions.
  const std::complex<double> gp(const double& t);
  const std::complex<double> gm(const double& t);
};

#endif