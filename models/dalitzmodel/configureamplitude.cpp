#include "configureamplitude.h"

using namespace DalitzModel;

void ConfigureAmplitude::build_model_from_file()
{
  DEBUG("Building model");
  build_phasespace_from_file();
  std::stringstream resos( m_config.get("resos") );
  std::string res;
  while ( resos >> res ) {
    build_resonance_from_file( res );
  }
  return;
}

void ConfigureAmplitude::build_phasespace_from_file()
{
  DEBUG("Building PhaseSpace");
  double mM = m_config.get<double>("mMoth");
  double m1 = m_config.get<double>("m1");
  double m2 = m_config.get<double>("m2");
  double m3 = m_config.get<double>("m3");
  PhaseSpace ps(mM,m1,m2,m3);
  m_amp.setPhaseSpace( ps );
}

void ConfigureAmplitude::build_resonance_from_file(std::string name)
{
  DEBUG("Building Resonances");
  std::stringstream res( m_config.get(name) );
  std::string type;
  res >> type;

  if ( type == "RBW" ) {
    appendRBW( name );
  } else if ( type == "CC" ) {
    appendFlatte( name );
  } else {
    WARNING("Unrecognised type " << type);
  }
  return;
}

void ConfigureAmplitude::appendRBW(std::string name)
{
  DEBUG(m_config.get(name));
  std::stringstream res( m_config.get(name) );

  int resoA, resoB, l;
  // Parameters.
  std::string type, mass, width, radius, coeff1, coeff2;
  res >> type >> resoA >> resoB >> l
      >> mass >> width >> radius
      >> coeff1 >> coeff2;

  Parameter m     = m_config.get<Parameter>(mass);
  Parameter w     = m_config.get<Parameter>(width);
  Parameter r     = m_config.get<Parameter>(radius);
  Parameter c1    = m_config.get<Parameter>(coeff1);
  Parameter c2    = m_config.get<Parameter>(coeff2);

  Coefficient c( c1 , c2 );

  LineShape::RelBreitWigner* comp = new LineShape::RelBreitWigner(name,c,resoA,resoB,m,w,l,r);
  m_amp.addResonance( comp );
  DEBUG(*comp);
}

void ConfigureAmplitude::appendFlatte(std::string name)
{
  std::stringstream res( m_config.get(name) );

  int resoA, resoB, l;
  // Parameters.
  std::string type, mass, width, radius, coeff1, coeff2, gam1name, gam2name, m1name, m2name;
  res >> type >> resoA >> resoB >> l
      >> mass >> width >> radius
      >> coeff1 >> coeff2
      >> gam1name >> gam2name >> m1name >> m2name;

  Parameter m     = m_config.get<Parameter>(mass);
  Parameter w     = m_config.get<Parameter>(width);
  Parameter r     = m_config.get<Parameter>(radius);
  Parameter c1    = m_config.get<Parameter>(coeff1);
  Parameter c2    = m_config.get<Parameter>(coeff2);
  Parameter gam1  = m_config.get<Parameter>(gam1name);
  Parameter gam2  = m_config.get<Parameter>(gam2name);
  Parameter m02a  = m_config.get<Parameter>(m1name);
  Parameter m02b  = m_config.get<Parameter>(m2name);

  Coefficient c( c1 , c2 );

  LineShape::Flatte* comp = new LineShape::Flatte(name,c,resoA,resoB,m,w,l,r,gam1,gam2,m02a,m02b);
  m_amp.addResonance(comp);
  DEBUG(*comp)
}