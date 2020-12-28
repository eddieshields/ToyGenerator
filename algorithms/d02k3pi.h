#ifndef TOYGEN_D02K3PI_H
#define TOYGEN_D02K3PI_H

#include "event.h"
#include "algorithm.h"
#include "random.h"
#include "msgservice.h"

#include <iostream>
#include <complex>
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
    dcs( "models/WSdcs.so" , "AMP" ),
    cf(  "models/WScf.so"  , "AMP" ),
    rs(  "models/RScf.so"  , "AMP" ),
    m_dcs_offset( 0.0601387 * std::exp( std::complex<double>(0,1) * 1.04827 * M_PI / 180. ) )
  {}
  ~D02K3Pi() {}

  virtual void operator() (Event& ev);

private:
  const double& x() const { return m_x; }
  const double& y() const { return m_y; }
  const std::complex<double>& z() const { return m_z; }
  std::complex<double> gp(const double& t);
  std::complex<double> gm(const double& t);

  const double               m_x = {0.004};
  const double               m_y = {0.006};
  const std::complex<double> m_z = {std::complex<double>(0.004,0.006)};

  const double               m_p = {1};
  const double               m_q = {1};

  const std::complex<double> m_dcs_offset;
  DynamicFCN<std::complex<double>(double const*, const int&) > dcs;
  DynamicFCN<std::complex<double>(double const*, const int&) > cf;
  DynamicFCN<std::complex<double>(double const*, const int&) > rs;
};

#endif