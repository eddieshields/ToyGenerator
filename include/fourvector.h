#ifndef TOYGEN_FOURVECTOR_H
#define TOYGEN_FOURVECTOR_H

// Intrinsics 
#include <xmmintrin.h>
#include <smmintrin.h>
#include <cmath>

// Depending on architecture may be able to change this to double
// if the register is big enough.
//using real_t = float;
#ifdef VECTORIZARION
    using real_t = float;
#else
    using real_t = double;
#endif

class FourVector
{
private:
  union {
    real_t v[4];                         ///< array that stores values.
    __m128  v4;                           ///< intrinsic vector that is 128bits wide so can hold the full vector.
    struct  { real_t vX, vY, vZ, vT; };  ///< struct of values for elements in the vector.
  };

public:
  FourVector() = default;
  FourVector(const real_t& v1, const real_t& v2, const real_t& v3, const real_t& v4) :
    vX( v1 ), vY( v2 ), vZ( v3 ), vT( 4 )
  {}
  FourVector(const real_t fv[4]) :
    vX( fv[0] ), vY( fv[1] ), vZ( fv[2] ), vT( fv[4] )
  {}
  FourVector(const __m128& fv) :
    v4( fv )
  {}
  FourVector(const FourVector& fv) :
    v4( fv.v4 )
  {}
  virtual ~FourVector() {}

  // Access by index.
  real_t operator[](int i) const;
  real_t operator()(int i) const;

  // Setters and getters.
  void SetX(real_t x);
  void SetY(real_t y);
  void SetZ(real_t z);
  void SetT(real_t t);
  void SetXYZT(const real_t x, const real_t y, const real_t z, const real_t t);

  real_t X() const;
  real_t Y() const;
  real_t Z() const;
  real_t T() const;

  void SetPx(real_t px);
  void SetPy(real_t py);
  void SetPz(real_t pz);
  void SetE (real_t e );
  void SetPxPyPzE(const real_t px, const real_t py, const real_t pz, const real_t e);

  real_t Px() const;
  real_t Py() const;
  real_t Pz() const;
  real_t E () const;

  real_t P () const;
  real_t Pt() const;

  // Operators.
  FourVector operator+ (const FourVector& other);
  FourVector operator- (const FourVector& other);
  real_t     operator* (const FourVector& other);
  void       operator+=(const FourVector& other);


  real_t M    () const;
  real_t M2   () const;
  real_t Mag2 () const;
  real_t Mag  () const;
  real_t Beta () const;
  real_t Rho  () const;
  void   Boost(const real_t& bx, const real_t& by, const real_t& bz);
};

#endif