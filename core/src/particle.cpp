#include "particle.h"

Particle Particle::operator+(Particle& part2)
{
  Particle part1 = *this;

  Particle part = Particle();
  part.m_stable = false;
  part.m_q = part1.m_q + part2.m_q;
  part.m_flavour = 0;

  part.m_p = part1.m_p + part2.m_p;
  part.m_true_p = part1.m_true_p + part2.m_true_p;
  
  return part;
}

Particle Particle::operator+=(Particle& part2)
{
  this->m_stable = false;
  this->m_q += part2.m_q ;
  this->m_flavour = 0;

  this->m_p += part2.m_p;
  this->m_true_p += part2.m_true_p;
  
  return *this;
}