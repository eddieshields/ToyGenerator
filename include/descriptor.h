#ifndef TOYGEN_DESCRIPTOR_H
#define TOYGEN_DESCRIPTOR_H

#include "msgservice.h"

#include <vector>
#include <string>
#include <sstream>

struct DecayDescriptor
{
  DecayDescriptor() = default;
  ~DecayDescriptor() {}
  void        decodeDecayDescriptor(std::string decay);
  void        printDecayDescriptor();
  void        getMotherName      (std::string decay);
  void        getDaughtersNames  (std::string decay);
  const int   getParticleCharge  (std::string particle);
  const int   getParticleFlavour (std::string particle);
  const bool  getChargedConjugate(std::string decay);
  std::string cleanParticle(std::string particle);

  std::vector<std::string>&  getParticles()       { return m_particles; }
  std::vector<int>&          getCharges()         { return m_charges; }
  std::vector<int>&          getFlavours()        { return m_flavours; }
  bool&                      getChargeConjugate() { return m_chcnj; }

private:
  std::vector<std::string>  m_particles;
  std::vector<int>          m_charges;
  std::vector<int>          m_flavours;
  bool                      m_chcnj;
};

#endif