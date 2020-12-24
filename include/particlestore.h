#ifndef TOYGEN_PARTICLESTORE_H
#define TOYGEN_PARTICLESTORE_H

// json.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <string>
#include <fstream>

struct ParticleStore {
  ParticleStore()
  {
    std::ifstream i("particles.json");
    i >> m_particles;
  }

  json m_particles;

  double operator()(std::string name, std::string variable) { return m_particles[name][variable].get<double>(); }
};

#endif