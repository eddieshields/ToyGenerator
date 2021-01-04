#ifndef TOYGEN_ANGULAR_H
#define TOYGEN_ANGULAR_H

#include <string>

namespace DalitzModel {

struct Angular 
{
  Angular() {}
  ~Angular() {}
  static void setZemach()   { m_zemach = true; }
  static void setHelicity() { m_zemach = false; }
  static void setAngular(std::string type)
  {
    if ( type == "Zemach" || type == "zemach" ) {
      m_zemach = true;
    } else {
      m_zemach = false;
    }
  }
  static bool isZemach()   { return m_zemach ? true : false; }
  static bool isHelicity() { return m_zemach ? false : true; }

  static bool m_zemach;
};

}

#endif