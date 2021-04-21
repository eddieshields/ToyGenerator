#include "descriptor.h"

void DecayDescriptor::decodeDecayDescriptor(std::string decay)
{
  getMotherName(decay);
  getDaughtersNames(decay);
  for (int i = 0; i < m_particles.size(); i++) {
    m_charges.push_back( getParticleCharge(m_particles[i]) );
    if ( m_charges[i] ) {
      m_flavours.push_back( 0 );
    } else {
      m_flavours.push_back( getParticleFlavour(m_particles[i]) );
    }
    m_pids.push_back( getParticlePID(m_particles[i]) );
  }
  m_chcnj = getChargedConjugate(decay);
  printDecayDescriptor();
}

void DecayDescriptor::printDecayDescriptor()
{
  std::string decay = m_particles[0]+" => ";
  for (int i = 1; i < m_particles.size(); i++) {
    decay += m_particles[i] + " ";
  }
  INFO("Decay = "+decay);
}

void DecayDescriptor::getMotherName(std::string decay)
{
  std::string mother = decay.replace(decay.find("=>") - 1,decay.size() - decay.find("=>") + 1, "");
  m_particles.push_back(mother);
}

void DecayDescriptor::getDaughtersNames(std::string decay)
{
  std::string daughters = decay.replace(0,m_particles[0].size()+4,"");

  std::istringstream ss(daughters);
  std::string daughter;
  while ( ss >> daughter ) {
    m_particles.push_back(daughter);
  }
}

const int DecayDescriptor::getParticleCharge(std::string particle)
{
  int posp = particle.find("+");
  int posm = particle.find("-");

  if ( posp != particle.npos ) {
    return +1;
  } else if ( posm != particle.npos ) {
    return -1;
  } 

  return 0;
}

const int DecayDescriptor::getParticleFlavour(std::string particle)
{
  int pos = particle.find("bar");
  if ( pos != particle.npos ) {
    return +1;
  }
  return -1;
}

const bool DecayDescriptor::getChargedConjugate(std::string decay)
{
  int pos1 = decay.find("cc");
  int pos2 = decay.find("CC");
  if ( pos1 != decay.npos && pos2 != decay.npos) {
    return false;
  }
  return true;
}

const real_t DecayDescriptor::getParticleMass(std::string particle)
{
  return gParticleStore(particle)->Mass();
}

const real_t DecayDescriptor::getParticleMass(const int particle)
{
  return gParticleStore(m_particles[particle])->Mass();
}

const int DecayDescriptor::getParticlePID(std::string particle)
{
  return gParticleStore(particle)->PdgCode();
}

const int DecayDescriptor::getParticlePID(const int particle)
{
  return gParticleStore(m_particles[particle])->PdgCode();
}

std::string DecayDescriptor::cleanParticle(std::string particle)
{
    int posp = particle.find("+");
    if ( posp != particle.npos ) particle.replace(posp,1,"");
    int posm = particle.find("-");
    if ( posm != particle.npos ) particle.replace(posm,1,"");
    int posf = particle.find("bar");
    if ( posf != particle.npos ) particle.replace(posf,3,"");

    return particle;
}

DecayDescriptor gDescriptor = DecayDescriptor();