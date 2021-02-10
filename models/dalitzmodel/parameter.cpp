#include "parameter.h"

using namespace DalitzModel;

// Initialise random variable.
bool Parameter::m_random = false;

double Parameter::operator=(const double& in)
{
  return m_par;
}

double Parameter::operator*(const double in) const
{
  return m_val * in;
}

template <class number>
const double Parameter::operator*(const number& in) const
{
  return m_val * in;
}

std::complex<double> Parameter::operator*(const std::complex<double>& in) const
{
  return m_val * in;
}

double Parameter::operator*(const Parameter& param) const
{
  return m_val * param.val();
}