#ifndef TOYGEN_RANDOM_H
#define TOYGEN_RANDOM_H

#include "msgservice.h"

#include <random>
#include <map>
#include <thread>

class Random
{
private:
  static int                                       _seed;
  /** Map between threads and their IDs. */
  static std::map<std::thread::id,std::mt19937_64> _engines;

  static std::mt19937_64                           _engine;

  static std::uniform_real_distribution< double >  _uniform;
  static std::exponential_distribution < double >  _exponential;
  static std::normal_distribution      < double >  _normal;
  static std::uniform_int_distribution < int >     _integer;

public:
  static void addThread(std::thread::id thread_id, int n)
  {
    _engines.insert( std::pair<std::thread::id,std::mt19937_64>{thread_id,std::mt19937_64()} );
    _engines.find( thread_id )->second.seed(_seed+n);
  }

  static void removeThread(std::thread::id thread_id)
  {
    _engines.erase( thread_id );
  }

  static std::mt19937_64& engine()
  {
    // Constructs thread in main thread.
    if ( _engines.empty() ) {
      _engines.insert( std::pair<std::thread::id,std::mt19937_64>{std::this_thread::get_id(),std::mt19937_64()} );
      _engines.find( std::this_thread::get_id() )->second.seed( _seed );
    }
    return _engines.find( std::this_thread::get_id() )->second;
  }

  static void setSeed( const unsigned& seed )
  { 
    _seed = seed;
  }

  static const double Rnd()
  {
    return _uniform( engine() );
  }

  static const double flat   ( const double& min = 0.0, const double& max = 1.0 )
  {
    return min + ( max - min ) * _uniform( engine() );
  }

  static const double uniform( const double& min = 0.0, const double& max = 1.0 )
  {
    return min + ( max - min ) * _uniform( engine() );
  }

  static const double exponential( const double& lambda = 1.0 )
  {
    return _exponential( _engine );
  }

  static const double normal( const double& mu = 0.0, const double& sigma = 1.0 )
  {
    return mu + sigma * _normal( _engine );
  }

  static const int integer( const int& a = 0, const int& b = 1 )
  {
    return _integer( _engine );
  }
};

#endif