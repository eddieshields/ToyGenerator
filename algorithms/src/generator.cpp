#include "generator.h"

const int kMAXP = 18;

void Generator::operator()(Event& ev)
{
  // Add particles.
  int cnj = 1;
  if ( Random::Bool() ) cnj *= -1;
  for (int i = 0; i < m_particles.size(); i++) {
    ev.particles().push_back( Particle() );
    ev.particle(i).charge() = m_charges[i] * cnj;
    ev.particle(i).flavour() = m_flavours[i];
  }

  // Generate event.
  auto daughts = Generate();

  for (int i = 1; i < m_particles.size(); i++) {
    ev.daughter(i).SetMomentum( daughts[i-1] );
  }
  // Set decay time.
  if ( !ev.mother().charge() ) ev.mother().flavour() = ( Random::Bool() ? 1 : -1 );
  ev.mother().isStable() = false;
  ev.mother().truetime() = ev.mother().time() = Random::exponential();

  return;
}

real_t Generator::q( real_t m, real_t m1, real_t m2 ) const
{
  return 0.5 * sqrt( m*m - 2*m1*m1 - 2*m2*m2 + (m1*m1-m2*m2)*(m1*m1-m2*m2)/(m*m) );
}

std::vector<FourVector> Generator::Generate()
{
  std::array<real_t, kMAXP> rno;
  std::array<real_t, kMAXP> pd;
  std::array<real_t, kMAXP> invMas; 
  std::vector<FourVector> rt;
  // Resize for daughters + mother;
  rt.resize(m_nt+1);

  rno[0] = 0;
  size_t n;
  real_t wt = m_wtMax;
  do {
    wt     = m_wtMax;
    rno[0] = 0;
    for( n = 1; n < m_nt - 1; n++ ) rno[n] = Random::Rnd(); // m_nt-2 random numbers
    rno[m_nt - 1]                          = 1;
    std::sort( rno.begin() + 1, rno.begin() + m_nt );
    real_t sum = 0;
    for ( n = 0; n < m_nt; n++ ) {
      sum += m_mass[n];
      invMas[n] = rno[n] * m_teCmTm + sum;
    }
    for ( n = 0; n < m_nt - 1; n++ ) {
      pd[n] = q( invMas[n + 1], invMas[n], m_mass[n + 1] );
      wt *= pd[n];
    }
  } while ( wt < Random::Rnd() );
  rt[0][0] = 0;
  rt[0][1] = pd[0];
  rt[0][2] = 0;
  rt[0][3] = sqrt( pd[0] * pd[0] + m_mass[0] * m_mass[0] );
  for(size_t i = 1 ; i != m_nt ; ++i ){  
    rt[i].SetPxPyPzE( 0, -pd[i-1], 0, sqrt( pd[i-1] * pd[i-1] + m_mass[i] * m_mass[i] ) );
    real_t cZ   = 2 * Random::Rnd() - 1;
    real_t sZ   = sqrt( 1 - cZ * cZ );
    real_t angY = 2 * M_PI * Random::Rnd();
    real_t cY   = cos(angY);
    real_t sY   = sin(angY);
    real_t beta  = (i == m_nt-1) ? 0 : pd[i] / sqrt( pd[i] * pd[i] + invMas[i] * invMas[i] );
    real_t gamma = (i == m_nt-1) ? 1 : 1./sqrt( 1 - beta*beta);    
    for (size_t j = 0; j <= i; j++ ) {
      real_t x          = rt[j][0];
      real_t y          = rt[j][1];
      real_t z          = rt[j][2];
      real_t E          = rt[j][3];
      rt[j][0] = cY * (cZ * x - sZ * y ) - sY * z;
      rt[j][1] = gamma*( sZ * x + cZ * y + beta * E );
      rt[j][2] = sY * (cZ * x - sZ * y )  + cY * z;
      rt[j][3] = gamma*( E + beta * (sZ *x + cZ*y) );
    }
  }
  return rt;
}

bool Generator::SetDecay(FourVector& P, std::vector<real_t>& masses)
{
  m_nt = masses.size();
  m_teCmTm = P.M();
  for (size_t n = 0; n < m_nt; n++) {
    m_mass[n] = masses[n];
    m_teCmTm -= masses[n];
  }
  if ( m_teCmTm <= 0 ) return 0 ; 
  real_t emmax = m_teCmTm + m_mass[0];
  real_t emmin = 0;
  real_t wtmax = 1;
  for (size_t n = 1; n < m_nt; n++) {
    emmin += m_mass[n - 1];
    emmax += m_mass[n];
    wtmax *= q( emmax, emmin, m_mass[n] );
  }
  m_wtMax = 1 / wtmax;
  return true;
}