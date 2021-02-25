#ifndef TOYGEN_TYPES_H
#define TOYGEN_TYPES_H

#include <complex>
#include <immintrin.h>

// Define real.
#ifdef DOUBLE_PRECISION
  using real_t = double;
  using __m = __m256d;
#else
  using real_t = float;
  using __m = __m128;
#endif

// Define complex.
using complex_t = std::complex<real_t>;

#endif