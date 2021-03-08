#include "resonance.h"

using namespace DalitzModel;

Resonance* Resonance::cnj_copy() const
{
  Resonance* reso = this->copy();
  if ( this->m_resoA == 2 ) {
    reso->m_resoA = this->m_resoB;
    reso->m_resoB = this->m_resoA;
  }  else {
    int noRes = 6 - this->m_resoA - this->m_resoB;
    reso->m_resoA = this->m_resoA;
    reso->m_resoB = noRes;
    reso->m_noRes = this->m_resoB;
  }
  reso->m_name = this->m_name + "_cnj";
  return reso;
}