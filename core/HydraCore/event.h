#ifndef TOYGEN_EVENT_H
#define TOYGEN_EVENT_H

#include "particle.h"
#include "msgservice.h"
#include "types.h"

#include <vector>
#include <map>
#include <string>

/*
TODO:
  Have event include particle classes that can be dealt with seprately.
  This class should deal with the event as a while and have access to daughter particles.
*/
class Event
{
friend class Generator;
public:
  Event() 
  {
    m_particles.reserve( 5 );
    m_data.reserve( ( 5 * 4 ) + 1);
  };
  virtual ~Event() {};

  real_t pdf = {1};
  real_t efficiency = {1};
  real_t weight = {1};
  bool   Accept = {true};

  std::vector<Particle>& particles() { return m_particles; }
  Particle& particle(int index)      { return m_particles[index]; }       
  Particle& mother()                 { return m_particles[0]; }
  Particle& daughter(int index)      { return m_particles[index]; }
  real_t* data()                     { makeData(); return m_data.data(); } 

  real_t&    operator[](std::string name) { return m_v[name]; }
  Particle& operator()(int index)         { return m_particles[index]; }

  std::vector<Particle>          m_particles;
  std::vector<real_t>            m_data;
  std::map<std::string,real_t>   m_v;

  void updateMasses()
  { 
    FourVector p12 = m_particles[1].momentum() + m_particles[2].momentum();
    FourVector p13 = m_particles[1].momentum() + m_particles[3].momentum();
    FourVector p23 = m_particles[2].momentum() + m_particles[3].momentum();

    m_v["mSq12"] = p12.M2();
    m_v["mSq13"] = p13.M2();
    m_v["mSq23"] = p23.M2();
  }

  void makeData()
  {
    std::vector<FourVector> pVec;
    for (int i = 0; i < m_particles.size(); i++) {
      pVec.push_back( m_particles[i].momentum() );
    }
    m_data.resize( 4 * pVec.size() );
    for( int i = 0 ; i < 4; ++i ){
      for( int j = 0 ; j < pVec.size(); ++j ){
        m_data[ 4 * j + i] = pVec[j][i];
      }
    }
  }

};

#endif