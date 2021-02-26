#include "d02k3pi.h"

void D02K3Pi::operator()(Event& ev)
{
  if ( ev.daughter(1).charge() == -1 ) {
    complex_t a = rs( ev.data() , -1 );
    real_t A = std::norm( a );
    ev.pdf = A;
    ev.weight = A;
  } else if ( ev.daughter(1).charge() == +1 ) {
    const real_t* data = ev.data();
    complex_t Adcs = m_dcs_offset * dcs( data , +1 );
    complex_t Acf  = cf( data , +1 );
    complex_t a = gp( ev.mother().time() )*Adcs + (m_q/m_p)*gm( ev.mother().time() )*Acf;
    real_t A = std::norm( a );
    ev.pdf = A;
    ev.weight = A;
  }
  return;
}

const real_t D02K3Pi::getR(Generator& gen)
{
  real_t n_dcs = 0;
  real_t n_cf  = 0;

  for (int i = 0; i < 1000000; i++) {
    Event ev;
    gen(ev);
    const real_t* data = ev.data();
    real_t adcs = std::norm( m_dcs_offset * dcs( data , +1 ) );
    real_t acf  = std::norm( cf( data , +1 ) );
    // Make sure that the amplitudes make sense.
    if ( std::isnan(adcs) || std::isnan(acf) ) continue;
      {
        n_dcs += adcs;
        n_cf  += acf;
      }
  }

  INFO("n_dcs = "+std::to_string(n_dcs));
  INFO("n_cf  = "+std::to_string(n_cf));
  real_t _r = std::sqrt( n_dcs/n_cf );
  INFO("r = "+std::to_string(_r));
  return _r;
}

complex_t D02K3Pi::gp(const real_t& t)
{
  complex_t I(0,1);
  return std::cos( -I * m_z * ( t/2 ) );
}

complex_t D02K3Pi::gm(const real_t& t)
{
  complex_t I(0,1);
  return std::sin( - I * m_z * ( t/2 ) );
}