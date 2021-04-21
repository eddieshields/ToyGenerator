// DalitzModel.
#include "parameter.h"
#include "configfile.h"
#include "configureamplitude.h"
#include "msgservice.h"
#include "clock.h"
#include "types.h"
#include "random.h"

#include <cxxopts.hpp>

int OnOff( const double& mSq23 ) {
  if      (   std::pow( 1.015 , 2 ) < mSq23 && mSq23 < std::pow( 1.025 , 2 ) ) return 0;
  else if ( ( std::pow( 0.900 , 2 ) < mSq23 && mSq23 < std::pow( 1.010 , 2 ) ) ||
            ( std::pow( 1.033 , 2 ) < mSq23 && mSq23 < std::pow( 1.100 , 2 ) ) ) return 1;
  return -1;
}


int main(int argc, char *argv[])
{
  cxxopts::Options options("ToyGenerator", "Program to generate D0->KsKK toys");
  options.add_options()
    ("m,model", "Model", cxxopts::value<std::string>()->default_value("belle2010"))
    ("s,seed", "Random seed", cxxopts::value<int>()->default_value("1"))
    ;
  auto parser = options.parse(argc, argv);

  Random::setSeed( parser["seed"].as<int>() );
  if ( parser["seed"].as<int>() != 1 ) DalitzModel::Parameter::ParameterUncertainty = DalitzModel::Uncertainty::Floating;

  DalitzModel::Coefficient::CoordinatesSystem = DalitzModel::Coordinates::Rectangular;
  DalitzModel::ConfigureAmplitude configure("cfg/"+parser["model"].as<std::string>()+".cfg");
  DalitzModel::Amplitude amp = configure();

 // Amplitudes [ ON : 0, OFF : 1 ][ A1 : 0, A2 : 1 ]
  real_t A[2][2];
  real_t step12 = ( amp.ps().mSq12max() - amp.ps().mSq12min() )/1000.;
  real_t step13 = ( amp.ps().mSq13max() - amp.ps().mSq13min() )/1000.;

  for (real_t mSq12 = amp.ps().mSq12min(); mSq12 < amp.ps().mSq12max(); mSq12 += step12 ) {
    for (real_t mSq13 = amp.ps().mSq13min(); mSq13 < amp.ps().mSq13max(); mSq13 += step13 ) {
      real_t mSq23 = amp.ps().mSqSum() - mSq12 - mSq13;
      int reg = OnOff( mSq23 );
      if ( reg < 0 ) continue;
      A[reg][0] += amp.A1Sq( mSq12 , mSq13 );
      A[reg][1] += amp.A2Sq( mSq12 , mSq13 );
    }
  }

  real_t fON  = A[0][1] / ( A[0][0] + A[0][1] );
  real_t fOFF = A[1][1] / ( A[1][0] + A[1][1] );
  real_t f    = fON - fOFF;

  PRINT("fON        = " << fON);
  PRINT("fOFF       = " << fOFF);
  PRINT("fON - fOFF = " << f);

  return 0;
}