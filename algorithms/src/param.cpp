#include "param.h"


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