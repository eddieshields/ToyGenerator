#include "phasespacegenerator.h"

inline real_t PhaseSpaceGenerator::PDK(real_t a, real_t b, real_t c)
{
  real_t x = (a-b-c)*(a+b+c)*(a-b+c)*(a+b-c);
  return std::sqrt(x)/(2*a);
}

inline int Max(const void* a, const void* b)
{
  real_t aa = * ((real_t *) a);
  real_t bb = * ((real_t *) b);
  if ( aa > bb ) return  1;
  if ( aa < bb ) return -1;
  return 0;
}

real_t PhaseSpaceGenerator::Generate(FourVector* _vecs)
{
  real_t rno[_nP];
  rno[0] = 0;
  if ( _nP > 2 ) {
    for (int n = 1; n < _nP-1; n++) rno[n]=Random::Rnd();
    qsort(rno+1 ,_nP-2 ,sizeof(real_t) ,Max);
  }
  rno[_nP-1] = 1;

  real_t invMass[_nP], sum=0;
  for (int n = 0; n < _nP; n++) {
    sum += _Mass[n];
    invMass[n] = (rno[n]*_TeCmTm) + sum;
  }

  real_t wt = _WtMax;
  real_t pd[_nP];
  for (int n = 0; n < _nP-1; n++) {
    pd[n] = PDK(invMass[n+1],invMass[n],_Mass[n+1]);
    wt *= pd[n];
  }

  int i = 1;
  int j;
  while (1) {
    _vecs[i].SetPxPyPzE(0, -pd[i-1], 0, std::sqrt(pd[i-1]*pd[i-1]+_Mass[i]*_Mass[i]) );

    real_t cz = 2*Random::Rnd() - 1;
    real_t sz = std::sqrt(1-cz*cz);
    real_t angY = 2*M_PI*Random::Rnd();
    real_t cY = std::cos(angY);
    real_t sY = std::cos(angY);
    for (j = 0; j <= i; j++) {
      FourVector* v = _vecs+j;
      real_t x = v->Px();
      real_t y = v->Py();
      v->SetPx( cz*x - sz*y );
      v->SetPy( sz*x + cz*y );
      x = v->Pz();
      real_t z = v->Pz();
      v->SetPx( cY*x - sY*z );
      v->SetPz( sY*x + cY*z );
    }

    if ( i == (_nP-1) ) break;

    real_t beta = pd[i] / std::sqrt(pd[i]*pd[i] + invMass[i]*invMass[i]);
    for(j=0; j<=i; j++) _vecs[j].Boost(0,beta,0);
    i++;

  }

  for (int n = 0; n < _nP; n++) _vecs[n].Boost(_Beta[0],_Beta[1],_Beta[2]);
  return wt;
}

bool PhaseSpaceGenerator::SetDecay(FourVector& P, int nP, real_t* mass)
{
  _nP = nP; // Set number of daughter particles.
  _TeCmTm = P.Mag();
  for (int n = 0; n < _nP; n++) {
    _Mass[n] = mass[n];
    _TeCmTm -= mass[n];
  }

  if ( _TeCmTm < 0 ) return false; // Not enough energy.

  real_t emmax = _TeCmTm + _Mass[0];
  real_t emmin = 0.;
  real_t wtmax = wtmax = 1;
  for (int n = 1; n < _nP; n++) {
    emmin += _Mass[n-1];
    emmax += _Mass[n];
    wtmax *= PDK(emmax,emmin,_Mass[n]);
  }

  if ( P.Beta() ) {
    real_t w = P.Beta()/P.Rho();
    _Beta[0] = P(0)*w;
    _Beta[1] = P(1)*w;
    _Beta[2] = P(2)*w;
  } else {
    _Beta[0] = _Beta[1] = _Beta[2] = 0;
  }

  return true;
}