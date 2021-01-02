#include "d02k3pi.h"

void D02K3Pi::operator()(Event& ev)
{
  if ( ev.daughter(1).charge() == -1 ) {
    std::complex<double> a = rs( ev.data() , -1 );
    double A = std::norm( a );
    ev.pdf = A;
    ev.weight = A;
  } else if ( ev.daughter(1).charge() == +1 ) {
    const double* data = ev.data();
    std::complex<double> Adcs = m_dcs_offset * dcs( data , +1 );
    std::complex<double> Acf  = cf( data , +1 );
    std::complex<double> a = gp( ev.mother().time() )*Adcs + (m_q/m_p)*gm( ev.mother().time() )*Acf;
    double A = std::norm( a );
    ev.pdf = A;
    ev.weight = A;
  }
  return;
}

const double D02K3Pi::getR(Generator& gen)
{
  double n_dcs = 0;
  double n_cf  = 0;

  for (int i = 0; i < 1000000; i++) {
    Event ev;
    gen(ev);
    const double* data = ev.data();
    double adcs = std::norm( m_dcs_offset * dcs( data , +1 ) );
    double acf  = std::norm( cf( data , +1 ) );
    // Make sure that the amplitudes make sense.
    if ( std::isnan(adcs) || std::isnan(acf) ) continue;
      {
        n_dcs += adcs;
        n_cf  += acf;
      }
  }

  INFO("n_dcs = "+std::to_string(n_dcs));
  INFO("n_cf  = "+std::to_string(n_cf));
  double _r = std::sqrt( n_dcs/n_cf );
  INFO("r = "+std::to_string(_r));
  return _r;
}

std::complex<double> D02K3Pi::gp(const double& t)
{
  std::complex<double> I(0,1);
  return std::cos( -I * m_z * ( t/2 ) );
}

std::complex<double> D02K3Pi::gm(const double& t)
{
  std::complex<double> I(0,1);
  return std::sin( - I * m_z * ( t/2 ) );
}