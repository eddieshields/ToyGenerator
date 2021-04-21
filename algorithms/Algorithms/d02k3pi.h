#ifndef TOYGEN_D02K3PI_H
#define TOYGEN_D02K3PI_H

#include "event.h"
#include "algorithm.h"
#include "generator.h"
#include "random.h"
#include "msgservice.h"
#include "types.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <dlfcn.h>

/// wrapper around function pointers/dlsym to give a somewhat friendlier interface 
template <class RETURN_TYPE, class ...IN_TYPES> class DynamicFCN;
template <class RETURN_TYPE, class ...IN_TYPES>
class DynamicFCN<RETURN_TYPE( IN_TYPES... )>
{
private:
  void* m_handle                        = {nullptr};
  RETURN_TYPE ( *m_fcn )( IN_TYPES... ) = {nullptr};

public:
  DynamicFCN() = default; 
  DynamicFCN( const std::string& lib, const std::string& name ) :
    m_handle(dlopen( lib.c_str(), RTLD_NOW )) 
    {
      m_fcn = (RETURN_TYPE( * )( IN_TYPES... ))dlsym( m_handle, name.c_str() );
      if ( m_fcn == nullptr ) std::cout << dlerror() << std::endl;
    }
  ~DynamicFCN() = default;
  RETURN_TYPE operator()( IN_TYPES... input ) const { return ( *m_fcn )( input... ); }
};

class D02K3Pi : public Algorithm
{
public:
  D02K3Pi(std::string name) : 
    Algorithm(name),
    m_dcs_offset( (real_t)0.0601387 * std::exp( complex_t(0,1)  * (real_t)1.04827 * (real_t)M_PI / (real_t)180. ) ),
    dcs( "models/WSdcs.so" , "AMP" ),
    cf(  "models/WScf.so"  , "AMP" ),
    rs(  "models/RScf.so"  , "AMP" )
  {}
  ~D02K3Pi() {}

  virtual void operator() (Event& ev);


  const real_t getR(Generator& gen);
private:
  const real_t& x() const { return m_x; }
  const real_t& y() const { return m_y; }
  const complex_t& z() const { return m_z; }
  complex_t gp(const real_t& t);
  complex_t gm(const real_t& t);

  const real_t               m_x = {0.004};
  const real_t               m_y = {0.006};
  const complex_t m_z = {complex_t(0.004,0.006)};

  const real_t               m_p = {1};
  const real_t               m_q = {1};

  const complex_t m_dcs_offset;
  DynamicFCN<complex_t(real_t const*, const int&) > dcs;
  DynamicFCN<complex_t(real_t const*, const int&) > cf;
  DynamicFCN<complex_t(real_t const*, const int&) > rs;
};

#endif