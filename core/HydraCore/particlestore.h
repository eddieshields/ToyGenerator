#ifndef TOYGEN_PARTICLESTORE_H
#define TOYGEN_PARTICLESTORE_H

#include "types.h"

// json.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <string>
#include <fstream>

struct ParticleStore {
  ParticleStore()
  {
    std::ifstream i("/Users/eddieshields/Documents/LHCb/projects/ToyGenerator/particles.json");
    i >> m_particles;
  }

  json m_particles;

  real_t operator()(std::string name, std::string variable) { return m_particles[name][variable].get<real_t>(); }
};

extern ParticleStore gParticleStore;

#endif