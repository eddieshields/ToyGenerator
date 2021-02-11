#ifndef DALITZMODEL_NAMED_H
#define DALITZMODEL_NAMED_H

#include "msgservice.h"

#include <string>
#include <map>

namespace DalitzModel {

class Named
{
private:
  const std::string m_name;

protected:
  static std::map<std::string,Named*> m_named;

public:
  Named(std::string& name) :
    m_name( name )
  {
    if ( m_named.find( m_name ) != m_named.end() ) {
      WARNING( m_name << " already exists!");
    }
    m_named.insert( std::pair<std::string,Named*>{ m_name , this } );
  }
  ~Named()
  {
    m_named.erase( m_name );
  }
};

} // namespace DalitzModel

#endif