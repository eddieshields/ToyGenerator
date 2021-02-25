#ifndef DALITZMODEL_RELBREITWIGNER_H
#define DALITZMODEL_RELBREITWIGNER_H

// DalitzModel.
#include "resonance.h"
#include "types.h"

namespace DalitzModel {
  namespace LineShape {

class RelBreitWigner : public Resonance
{
public:
  RelBreitWigner() = default;
  RelBreitWigner(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r) :
    Resonance( name , coeff , resoA , resoB , mass , width , l , r )
  {}
  RelBreitWigner(std::string& name, const double& coeff1, const double& coeff2,
            const int& resoA, const int& resoB,
            const double& mass, const double& width,
            const int& l, const double& r) :
    Resonance( name , coeff1 , coeff2 , resoA , resoB , mass , width , l , r )
  {}
  RelBreitWigner(const RelBreitWigner& other) :
    Resonance( other )
  {}
  ~RelBreitWigner() {}

  // Implementation of propagator.
  /** Relativistic Breit Wigner propagator.
   * 
   * \f[
   *   T_{R}\left( m_{AB} \right) = \frac{1}{m_{R}^{2} - m_{AB}^{2} - im_{R}\Gamma_{AB}\left( m_{AB} \right)}
   * \f]
   */
  const complex_t propagator(const PhaseSpace& ps, const real_t& mSqAB) const
  {
    complex_t I( (real_t)0., (real_t)1. );
    return (real_t)1. /( mSq() - mSqAB - ( m() * I * runningWidth(ps,mSqAB) ) );
  }
  
  /** Running width $\f \Gamma_{AB}\left( m_{AB} \right)\f$
   * 
   * \f[
   *   \Gamma_{AB}\left( m_{AB} \right) = \Gamma_{R} \left( \frac{q}{q_{0}} \right)^{2L+1}
   *                                      \left( \frac{m_{R}}{m_{AB}} \right)
   *                                      B_{L}^{'2}\left( q,q_{0} \right)
   * \f]
   */
  const real_t runningWidth(const PhaseSpace& ps, const real_t& mSqAB) const
  {
    return width() * std::pow( q( ps, mSqAB )/q( ps, mSq() ) , (2*m_l + 1) ) * ( m() / std::sqrt( mSqAB ) ) * std::pow( blattWeisskopfPrime(ps,mSqAB) , 2 );
  }

  RelBreitWigner* copy() const
  {
    return new RelBreitWigner(*this);
  }
};

  } // namespace LineShape
} // namespace DalitzModel

#endif