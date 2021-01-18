#include "dalitzamplitude.h"
#include "configureamplitude.h"
#include "descriptor.h"
#include "msgservice.h"

int OnOff(double& mSq23)
{
  if      (   std::pow( 1.015 , 2 ) < mSq23 && mSq23 < std::pow( 1.025 , 2 ) )   return 1;
  else if ( ( std::pow( 0.900 , 2 ) < mSq23 && mSq23 < std::pow( 1.010 , 2 ) ) ||
            ( std::pow( 1.033 , 2 ) < mSq23 && mSq23 < std::pow( 1.100 , 2 ) ) ) return 0;

  return -1;
}

int main()
{
  gDescriptor( "D0 => KS0 K+ K-" );
  DalitzModel::ConfigureAmplitude configure( "cfg/belle2010.cfg" );
  DalitzModel::DalitzAmplitude amp;
  configure( amp );

  double mSq12step = 1000;
  double mSq12min = amp.phasespace().mSq12min();
  double mSq12max = amp.phasespace().mSq12max();

  double mSq13step = 1000;
  double mSq13min = amp.phasespace().mSq13min();
  double mSq13max = amp.phasespace().mSq13max();

  double mSqSum = amp.phasespace().mSqSum();

  double A[2][2];
  for (double mSq12 = mSq12min; mSq12 < mSq12max; mSq12 += mSq12step) {
    for ( double mSq13 = mSq13min; mSq13 < mSq13max; mSq13 += mSq13step) {
      double mSq23 = mSqSum - mSq12 - mSq13;
      int reg = OnOff( mSq23 );
      if ( reg < 0 ) continue;
      A[reg][0] += amp.A1Sq(mSq12,mSq13,mSq23);
      A[reg][1] += amp.A2Sq(mSq12,mSq13,mSq23);
    }
  }

  double fON  = A[0][1] / ( A[0][0] + A[0][1] );
  double fOFF = A[1][1] / ( A[1][0] + A[1][1] );
  double f    = fON - fOFF;

  INFO("fON  = " << fON);
  INFO("fOFF = " << fOFF);
  INFO("f    = " << f);

  return 0;
}