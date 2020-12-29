#include "param.h"

const double Param::eval(Particle& part)
{
  
  switch (m_type)
  {
  case Param::Q:
    return part.charge();
  case Param::T:
    return part.time();
  case Param::M:
    return part.momentum().M();
  case Param::MSq:
    return part.momentum().M2();
  case Param::PX:
    return part.momentum().Px();
  case Param::PY:
    return part.momentum().Py();
  case Param::PZ:
    return part.momentum().Pz();
  case Param::PT:
    return part.momentum().Pt();
  case Param::P:
    return part.momentum().P();
  case Param::E:
    return part.momentum().E();
  default:
    FATAL(getName(m_type)+" does not exist.")
    return part.momentum().M();
  }
}


const Param::Type Param::getParamFromString(std::string param)
{
  if ( param == "weight" || param == "Weight" || param == "w") {
    return Param::W;
  } else if ( param == "pdf" || param == "Pdf" ) {
    return Param::PDF;
  } else if ( param == "q" || param == "Q" ) {
    return Param::Q;
  } else if ( param == "t" || param == "time" ) {
    return Param::T;
  } else if ( param == "M" ) {
    return Param::M;
  } else if ( param == "MSq" ) {
    return Param::MSq;
  } else if ( param == "Px" ) {
    return Param::PX;
  } else if ( param == "Py" ) {
    return Param::PY;
  } else if ( param == "Pz" ) {
    return Param::PZ;
  } else if ( param == "Pt" ) {
    return Param::PT;
  } else if ( param == "P" ) {
    return Param::P;
  } else if ( param == "E" ) {
    return Param::E;
  } else {
    FATAL(param+" does not exist.")
    return Param::M;
  }
}

const std::string Param::getName(Param::Type param)
{
  switch(param)
  {
  case Param::W:
    return "weight";
  case Param::PDF:
    return "pdf";
  case Param::Q:
    return "Q";
  case Param::T:
    return "t"; 
  case Param::M:
    return "M"; 
  case Param::MSq:
    return "MSq"; 
  case Param::PX:
    return "Px"; 
  case Param::PY:
    return "Py"; 
  case Param::PZ:
    return "Pz"; 
  case Param::PT:
    return "Pt"; 
  case Param::P:
    return "P"; 
  case Param::E:
    return "E"; 
  default:
    FATAL("Param does not exist.");
    return "";
  };
}