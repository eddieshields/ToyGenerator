#ifndef TOYGEN_EVENT_H
#define TOYGEN_EVENT_H

#include "particle.h"

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
  ~Event() {};

  double pdf = {1};
  double efficiency = {1};
  double weight = {1};
  bool   Accept = {false};

  std::vector<Particle>& particles() { return m_particles; }
  Particle& particle(int index)      { return m_particles[index]; }       
  Particle& mother()                 { return m_particles[0]; }
  Particle& daughter(int index)      { return m_particles[index]; }
  double* data()                     { makeData(); return m_data.data(); } 

  double&    operator[](std::string name) { return m_v[name]; }
  Particle& operator()(int index)         { return m_particles[index]; }

  std::vector<Particle> m_particles;
  std::vector<double>   m_data;
  std::map<std::string,double>   m_v;

  void updateMasses()
  {  
    TLorentzVector p1 = m_particles[1].momentum();
    TLorentzVector p2 = m_particles[2].momentum();
    TLorentzVector p3 = m_particles[3].momentum();

    TLorentzVector p12 = p1 + p2;
    TLorentzVector p13 = p1 + p3;
    TLorentzVector p23 = p2 + p3;
  
    m_v["mSq12"] = p12.M2();
    m_v["mSq13"] = p13.M2();
    m_v["mSq23"] = p23.M2();
  }

  void makeData()
  {
    std::vector<TLorentzVector> pVec;
    for (auto& p : m_particles) {
      pVec.push_back( p.momentum() );
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