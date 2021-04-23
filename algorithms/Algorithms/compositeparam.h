#ifndef TOYGEN_COMPOSITE_PARAM
#define TOYGEN_COMPOSITE_PARAM

#include "particleparam.h"

template <Param::Type P>
class CompositeParam : public ParticleParam<P>
{
public:
  CompositeParam() :
    ParticleParam<P>()
  {}
  template<typename... ARGS>
  CompositeParam(std::string name, std::string param, int index, ARGS... indices) :
    ParticleParam<P>(name,param,index)
  {
    addIndex(indices...);
  }
  ~CompositeParam() {};

  template<typename... ARGS>
  void addIndex(int index, ARGS... indices) 
  {
    m_particles_indices.push_back(index);
    addIndex(indices...);
  }
  void addIndex(int index)
  {
    m_particles_indices.push_back(index);
  }

  inline void operator()(Event& ev) override final
  {
    Particle part = ev.particle(ParticleParam<P>::m_particle_index);
    for (auto& i : m_particles_indices) {
      part += ev.particle(i);
    }
    ev[ParticleParam<P>::m_name] = ParticleParam<P>::m_evaluation(part);
  }
private:
  std::vector<int> m_particles_indices;
};

#endif