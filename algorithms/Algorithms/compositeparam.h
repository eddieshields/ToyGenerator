#ifndef TOYGEN_COMPOSITE_PARAM
#define TOYGEN_COMPOSITE_PARAM

#include "particleparam.h"

class CompositeParam : public ParticleParam 
{
public:
  CompositeParam() :
    ParticleParam()
  {}
  template<typename... ARGS>
  CompositeParam(std::string name, std::string param, int index, ARGS... indices) :
    ParticleParam(name,param,index)
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

  virtual void operator()(Event& ev);
private:
  std::vector<int> m_particles_indices;
};

#endif