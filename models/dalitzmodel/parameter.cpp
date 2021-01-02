#include "parameter.h"

using namespace DalitzModel;

// Initialise random variable.
bool Parameter::_random = false;

const double Parameter::val() const
{
  if ( _random ) return _par + _err;
  else return _par;
}

Parameter* Parameter::copy()
{
  return this;
}

double Parameter::operator=(const double& in)
{
  return _par;
}

double Parameter::operator*(const double in) const
{
  double out;
  if ( _random ) out = ( _par + _err ) * in;
  else out = _par * in;
  return out;
}

template <class number>
const double Parameter::operator*(const number& in) const
{
  number out;
  if ( _random ) out = ( _par + _err ) * in;
  else out = _par * in;
  return out;
}

std::complex<double> Parameter::operator*(const std::complex<double>& in) const
{
  std::complex<double> out;
  if ( _random ) out = ( _par + _err ) * in;
  else out = _par * in;
  return out;
}

double Parameter::operator*(const Parameter& param) const
{
  double out;
  if ( _random ) out = ( _par + _err ) * param.val();
  else out = _par * param.val();
  return out;
}