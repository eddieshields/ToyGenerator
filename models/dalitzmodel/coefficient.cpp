#include "coefficient.h"

using namespace DalitzModel;

bool Coeff::m_rectangular = true;

std::complex< double > Coeff::operator*(const double& num)
{
  if ( !m_rectangular ) return std::polar( _c1.val(), _c2.val() )*num;
  return std::complex<double>( _c1.val(), _c2.val() )*num;
}

std::complex< double > Coeff::operator*(const std::complex< double >& num)
{
  if ( !m_rectangular ) return std::polar( _c1.val(), _c2.val() )*num;
  return std::complex<double>( _c1.val(), _c2.val() )*num;
}

std::complex< double > Coeff::operator*(const Parameter& num)
{
  if ( !m_rectangular ) return std::polar( _c1.val(), _c2.val() )*num.val();
  return std::complex<double>( _c1.val(), _c2.val() )*num.val();
}
/*
std::ostream& Coeff::operator<<(std::ostream& os, const Coeff& c)
{
  os << "(" << c._c1.val() << "," << c._c2.val(); 
  return os;
}

std::istream& Coeff::operator>>(std::istream& is, Coeff& c)
{
  is >> "(" >>c._c1.val() >> "," >> c._c2.val(); 
  return is;
}
*/