// Define operations based on architecture.
#include <immintrin.h>

#ifdef DOUBLE_PRECISION
  #define intrinsic_add( X , Y ) _mm256d_add_pd( X , Y )
  #define intrinsic_sub( X , Y ) _mm256d_sub_pd( X , Y )
  #define intrinsic_mul( X , Y ) _mm256d_mul_pd( X , Y )
  #define intrinsic_div( X , Y ) _mm256d_div_pd( X , Y )
  #define intrinsic_set1( X... )    _mm256d_set1_pd( ...X )
  #define intrinsic_setr( X... )    _mm256d_setr_pd( ...X )
  #define intrinsic_loadu( X )   _mm256d_loadu_pd( X )
  #define intrinsic_hadd( X , Y ) _mm256d_hadd_pd( X , Y )
  #define intrinsic_first_element( X ) _mm_cvtsd_f64( X )
#else
  #define intrinsic_add( X , Y ) _mm_add_ps( X , Y )
  #define intrinsic_sub( X , Y ) _mm_sub_ps( X , Y )
  #define intrinsic_mul( X , Y ) _mm_mul_ps( X , Y )
  #define intrinsic_div( X , Y ) _mm_div_ps( X , Y )
  #define intrinsic_set1( X )    _mm_set1_ps( X )
  #define intrinsic_setr( X , Y , Z , T) _mm_setr_ps( X , Y , Z , T )
  #define intrinsic_loadu( X )   _mm_loadu_ps( X )
  #define intrinsic_hadd(X , Y ) _mm_hadd_ps( X , Y )
  #define intrinsic_first_element( X ) _mm_cvtss_f32( X )
#endif