#include "generator.h"

void Generator::operator()(Event& ev)
{
  // Need to add multithreaded support so we dont need new TGen in each loop.
  // Generate event.
  TGenPhaseSpace phsp(m_phsp);
  phsp.Generate();

  // Add particles.
  int cnj = 1;
  if ( rand() % 2 ) cnj *= -1;;
  for (int i = 0; i < m_particles.size(); i++) {
    ev.particles().push_back( Particle() );
    ev.particle(i).charge() = m_charges[i] * cnj;
    ev.particle(i).flavour() = m_flavours[i];
    if ( !i ) continue;
    ev.daughter(i).momentum() = *phsp.GetDecay(i-1);
  }

  // Set decay time.
  ev.mother().isStable() = false;
  ev.mother().time() = Random::exponential();

  return;
}

void Generator::decodeDecayDescriptor(std::string decay)
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
    m_particles[i] = cleanParticle(m_particles[i]);
  }
  m_chcnj = getChargedConjugate(decay);
  printDecayDescriptor();
}

void Generator::printDecayDescriptor()
{
  std::string decay = m_particles[0]+" => ";
  for (int i = 1; i < m_particles.size(); i++) {
    if ( m_charges[i] == +1 ) {
      decay += m_particles[i] + "+ ";
    } else if ( m_charges[i] == -1 ) {
      decay += m_particles[i] + "- ";
    } else if ( m_flavours[i] == -1 ) {
      decay += m_particles[i] + "bar ";
    } else {
      decay += m_particles[i] + " ";
    }
  }
  INFO("Decay = "+decay);
}

void Generator::getMotherName(std::string decay)
{
  std::string mother = decay.replace(decay.find("=>") - 1,decay.size() - decay.find("=>") + 1, "");
  m_particles.push_back(mother);
}

void Generator::getDaughtersNames(std::string decay)
{
  std::string daughters = decay.replace(0,m_particles[0].size()+4,"");

  std::istringstream ss(daughters);
  std::string daughter;
  while ( ss >> daughter ) {
    m_particles.push_back(daughter);
  }
}

const int Generator::getParticleCharge(std::string particle)
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

const int Generator::getParticleFlavour(std::string particle)
{
  int pos = particle.find("bar");
  if ( pos != particle.npos ) {
    return +1;
  }
  return -1;
}

const bool Generator::getChargedConjugate(std::string decay)
{
  int pos1 = decay.find("cc");
  int pos2 = decay.find("CC");
  if ( pos1 != decay.npos && pos2 != decay.npos) {
    return false;
  }
  return true;
}

std::string Generator::cleanParticle(std::string particle)
{
    int posp = particle.find("+");
    if ( posp != particle.npos ) particle.replace(posp,1,"");
    int posm = particle.find("-");
    if ( posm != particle.npos ) particle.replace(posm,1,"");
    int posf = particle.find("bar");
    if ( posf != particle.npos ) particle.replace(posf,3,"");

    return particle;
}