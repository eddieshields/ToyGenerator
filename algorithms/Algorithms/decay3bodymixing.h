#ifndef TOYGEN_DECAY3BODYMIXING_H
#define TOYGEN_DECAY3BODYMIXING_H

#include "event.h"
#include "algorithm.h"
#include "configureamplitude.h"
#include "amplitude.h"
#include "types.h"

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
  const real_t               x() const { return m_x; }
  const real_t               y() const { return m_y; }
  const real_t               p() const { return m_p; }
  const real_t               q() const { return m_q; }
  // z = -(y+ix)
  const complex_t z() const { return m_z; }

  // Setters.
  void setX(real_t x) { m_x = x; m_z = complex_t(-m_y,-m_x); }
  void setY(real_t y) { m_y = y; m_z = complex_t(-m_y,-m_x); }
  void setP(real_t p) { m_p = p; }
  void setQ(real_t q) { m_q = q; }

  // Operator.
  virtual void operator() (Event& ev);
private:
  DalitzModel::Amplitude m_amp;

  // Mixing parameters.
  real_t m_x = {0.004};
  real_t m_y = {0.006};
  real_t m_p = {1};
  real_t m_q = {1};
  complex_t m_z = {complex_t(-0.006,-0.004)};

  // Mixing functions.
  const complex_t gp(const real_t& t);
  const complex_t gm(const real_t& t);
};

#endif