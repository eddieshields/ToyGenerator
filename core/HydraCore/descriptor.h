#ifndef TOYGEN_DESCRIPTOR_H
#define TOYGEN_DESCRIPTOR_H

#include "particlestore.h"
#include "msgservice.h"
#include "types.h"

#include <vector>
#include <string>
#include <sstream>

struct DecayDescriptor
{
  DecayDescriptor() {};
  ~DecayDescriptor() {}
  void         decodeDecayDescriptor(std::string decay);
  void         printDecayDescriptor();
  void         getMotherName      (std::string decay);
  void         getDaughtersNames  (std::string decay);
  const int    getParticleCharge  (std::string particle);
  const int    getParticleFlavour (std::string particle);
  const bool   getChargedConjugate(std::string decay);
  const real_t getParticleMass    (std::string particle);
  const real_t getParticleMass    (const int particle);
  std::string cleanParticle(std::string particle);

  std::vector<std::string>&  getParticles()       { return m_particles; }
  std::vector<int>&          getCharges()         { return m_charges; }
  std::vector<int>&          getFlavours()        { return m_flavours; }
  bool&                      getChargeConjugate() { return m_chcnj; }

  void operator()(std::string decay) { decodeDecayDescriptor(decay); }
  DecayDescriptor operator=(std::string decay) { decodeDecayDescriptor(decay); return *this; }
private:
  std::vector<std::string>  m_particles;
  std::vector<int>          m_charges;
  std::vector<int>          m_flavours;
  bool                      m_chcnj;
};


extern DecayDescriptor gDescriptor;

#endif