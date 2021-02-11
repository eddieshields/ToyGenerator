#include "fourvector.h"

real_t& FourVector::operator[](int i)       { return v[i]; }
real_t  FourVector::operator()(int i) const { return v[i]; }

void FourVector::SetX(real_t x) { vX = x; }
void FourVector::SetY(real_t y) { vY = y; }
void FourVector::SetZ(real_t z) { vZ = z; }
void FourVector::SetT(real_t t) { vT = t; }
void FourVector::SetXYZT(const real_t x, const real_t y, const real_t z, const real_t t)
{
  vX = x;
  vY = y;
  vZ = z;
  vT = t;
}

real_t FourVector::X() const { return vX; }
real_t FourVector::Y() const { return vY; }
real_t FourVector::Z() const { return vZ; }
real_t FourVector::T() const { return vT; }

void FourVector::SetPx(real_t px) { vX = px; }
void FourVector::SetPy(real_t py) { vY = py; }
void FourVector::SetPz(real_t pz) { vZ = pz; }
void FourVector::SetE (real_t e ) { vT = e;  }
void FourVector::SetPxPyPzE(const real_t px, const real_t py, const real_t pz, const real_t e)
{
  SetXYZT( px, py, pz, e );
}

real_t FourVector::Px() const { return vX; }
real_t FourVector::Py() const { return vY; }
real_t FourVector::Pz() const { return vZ; }
real_t FourVector::E () const { return vT; }

FourVector FourVector::operator+(const FourVector& other)
{
  #ifdef VECTORIZATION
    return FourVector( _mm_add_ps( this->v4 , other.v4) );
  #else
    return FourVector( this->vX + other.vX , this->vY + other.vY, this->vZ + other.vZ, this->vT + other.vT );
  #endif
}

FourVector FourVector::operator-(const FourVector& other)
{
  #ifdef VECTORIZATION
    return FourVector( _mm_sub_ps( this->v4 , other.v4 ) );
  #else
    return FourVector( this->vX - other.vX , this->vY - other.vY, this->vZ - other.vZ, this->vT - other.vT );
  #endif
}

real_t FourVector::operator*(const FourVector& other)
{
  #ifdef VECTORIZATION
    __m128 t4;
    // Multiply the two vectors together v1 = {v11,v12,v13,v14}, v2 = {v21,v22,v23,v24}.
    //  t = {v11*v21,v12*v22,v13*v23,v14*v24}.
    t4 = _mm_mul_ps( this->v4 , other.v4 );
    // Hadd the two vectors, now t becomes.
    // t = {v11*v21 + v12*v22, v13*v23 + v14*v24, v11*v21 + v12*v22, v13*v23 + v14*v24}.
    t4 = _mm_hadd_ps( t4 , t4 );
    // Hadd again so all elements become
    // ti = v11*v21 + v12*v22 + v13*v23 + v14*v24.
    t4 = _mm_hadd_ps( t4 , t4 );
    // Return first element of t1.
    // All elements are the same, the dot product of v1 and v2.
    return _mm_cvtss_f32(t4);
  #else
    return (this->vX*other.vX + this->vY*other.vY + this->vZ*other.vZ + this->vT*other.vT);
  #endif
}

void FourVector::operator+=(const FourVector& other)
{
  #ifdef VECTORIZATION
    v4 = _mm_add_ps( this->v4 , other.v4 );
  #else
    vX += other.vX;
    vY += other.vY;
    vZ += other.vZ;
    vT += other.vT;
  #endif
}

real_t FourVector::M() const
{
  return Mag();
}

real_t FourVector::M2() const
{
  return Mag2();
}

real_t FourVector::Mag2() const 
{
  return vT*vT - vX*vX - vY*vY - vZ*vZ; 
}

real_t FourVector::Mag() const
{
  real_t mm = Mag2();
  return mm < 0.0 ? -std::sqrt( -mm ) : std::sqrt( mm );
}

real_t FourVector::Beta() const
{
  return (vX*vX + vY*vY + vZ*vZ) / vT;
}

real_t FourVector::Rho() const
{
  real_t mm = vX*vX + vY*vY + vZ*vZ;  // v3.Mag2()
  return  mm < 0.0 ? -std::sqrt( -mm ) : std::sqrt( mm ); // v3.Maf();
}

real_t FourVector::P() const
{
  return std::sqrt(vX*vX + vY*vY + vZ*vZ);
}

real_t FourVector::Pt() const
{
  return std::sqrt(vX*vX + vY*vY);
}


void FourVector::Boost(const real_t& bx, const real_t& by, const real_t& bz)
{
  real_t b2 = bx*bx + by*by + bz*bz;
  real_t gamma = 1.0 / std::sqrt( 1.0 - b2 );
  real_t bp = bx*X() + by*Y() +bz*Z();
  real_t gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  vX = X() + gamma2*bp*bx + gamma*bx*T();
  vY = Y() + gamma2*bp*by + gamma*by*T();
  vZ = Z() + gamma2*bp*bz + gamma*bz*T();
  vT = gamma*(T() + bp);
}