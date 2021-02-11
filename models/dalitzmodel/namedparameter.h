#ifndef DALITZMODEL_NAMEDPARAMETER_H
#define DALITZMODEL_NAMEDPARAMETER_H

#include "parameter.h"

#include <string>
#include <map>

namespace DalitzModel{


class NamedParameter
{
private:
  static std::map<std::string,Parameter*> m_parameters;
  Parameter* m_param;
  std::string m_name;
  double& m_value_ref;
  double& m_error_ref;
public:
  double& m_state_ref;

  NamedParameter(std::string& name, const double& val, const double& err = 0) :
    m_name( name ),
    m_param( find_parameter(name,val,err) ),
    m_value_ref( m_param->m_value ),
    m_error_ref( m_param->m_error ),
    m_state_ref( m_param->m_state )
  {}
  NamedParameter(const NamedParameter& named_param) :
    m_name( named_param.m_name ),
    m_param( named_param.m_param ),
    m_value_ref( named_param.m_value_ref ),
    m_error_ref( named_param.m_error_ref ),
    m_state_ref( named_param.m_state_ref )
  {}
  virtual ~NamedParameter() {}

  Parameter* find_parameter(std::string& name, const double& val, const double& err = 0)
  {
    if ( m_parameters.find(name) == m_parameters.end() ) {
      Parameter* param = new Parameter(val,err);
      m_parameters.insert( std::pair<std::string,Parameter*>{ name , std::move( param ) } ); 
    }
    return m_parameters[name];
  }

  // Operators.
  friend const double operator+(const NamedParameter& left, const NamedParameter& right)
  {
    return left.m_state_ref + right.m_state_ref;
  }
  
  friend const double operator-(const NamedParameter& left, const NamedParameter& right)
  {
    return left.m_state_ref - right.m_state_ref;
  }
  
  friend const double operator*(const NamedParameter& left, const NamedParameter& right)
  {
    return left.m_state_ref * right.m_state_ref;
  }
  
  friend const double operator/(const NamedParameter& left, const NamedParameter& right)
  {
    return left.m_state_ref / right.m_state_ref;
  }
  
  friend const double operator+(const NamedParameter& left, const int& right)
  {
    return left.m_state_ref + (double)right;
  }
  
  friend const double operator-(const NamedParameter& left, const int& right)
  {
    return left.m_state_ref - (double)right;
  }
  
  friend const double operator*(const NamedParameter& left, const int& right)
  {
    return left.m_state_ref * (double)right;
  }
  
  friend const double operator/(const NamedParameter& left, const int& right)
  {
    return left.m_state_ref / (double)right;
  }
  
  friend const double operator+(const NamedParameter& left, const double& right)
  {
    return left.m_state_ref + right;
  }
  
  friend const double operator-(const NamedParameter& left, const double& right)
  {
    return left.m_state_ref - right;
  }
  
  friend const double operator*(const NamedParameter& left, const double& right)
  {
    return left.m_state_ref * right;
  }
  
  friend const double operator/(const NamedParameter& left, const double& right)
  {
    return left.m_state_ref / right;
  }
  
  friend const double operator+(const NamedParameter& left, const float& right)
  {
    return left.m_state_ref + (double)right;
  }
  
  friend const double operator-(const NamedParameter& left, const float& right)
  {
    return left.m_state_ref - (double)right;
  }
  
  friend const double operator*(const NamedParameter& left, const float& right)
  {
    return left.m_state_ref * (double)right;
  }
  
  friend const double operator/(const NamedParameter& left, const float& right)
  {
    return left.m_state_ref / (double)right;
  }
  
  friend const complex_t operator+(const NamedParameter& left, const complex_t& right)
  {
    return left.m_state_ref + right;
  }
  
  friend const complex_t operator-(const NamedParameter& left, const complex_t& right)
  {
    return left.m_state_ref - right;
  }
  
  friend const complex_t operator*(const NamedParameter& left, const complex_t& right)
  {
    return left.m_state_ref * right;
  }
  
  friend const complex_t operator/(const NamedParameter& left, const complex_t& right)
  {
    return left.m_state_ref / right;
  }
  
  friend const double operator+(const int& left, const NamedParameter& right)
  {
    return (double)left + right.m_state_ref;
  }
  
  friend const double operator-(const int& left, const NamedParameter& right)
  {
    return (double)left - right.m_state_ref;
  }
  
  friend const double operator*(const int& left, const NamedParameter& right)
  {
    return (double)left * right.m_state_ref;
  }
  
  friend const double operator/(const int& left, const NamedParameter& right)
  {
    return (double)left / right.m_state_ref;
  }
  
  friend const double operator+(const double& left, const NamedParameter& right)
  {
    return left + right.m_state_ref;
  }
  
  friend const double operator-(const double& left, const NamedParameter& right)
  {
    return left - right.m_state_ref;
  }
  
  friend const double operator*(const double& left, const NamedParameter& right)
  {
    return left * right.m_state_ref;
  }
  
  friend const double operator/(const double& left, const NamedParameter& right)
  {
    return left / right.m_state_ref;
  }
  
  friend const double operator+(const float& left, const NamedParameter& right)
  {
    return (double)left + right.m_state_ref;
  }
  
  friend const double operator-(const float& left, const NamedParameter& right)
  {
    return (double)left - right.m_state_ref;
  }
  
  friend const double operator*(const float& left, const NamedParameter& right)
  {
    return (double)left * right.m_state_ref;
  }
  
  friend const double operator/(const float& left, const NamedParameter& right)
  {
    return (double)left / right.m_state_ref;
  }
  
  friend const complex_t operator+(const complex_t& left, const NamedParameter& right)
  {
    return left + right.m_state_ref;
  }
  friend const complex_t operator-(const complex_t& left, const NamedParameter& right)
  {
    return left - right.m_state_ref;
  }
  friend const complex_t operator*(const complex_t& left, const NamedParameter& right)
  {
    return left * right.m_state_ref;
  }
  friend const complex_t operator/(const complex_t& left, const NamedParameter& right)
  {
    return left / right.m_state_ref;
  }
};

} // namespace DalitzModel

#endif