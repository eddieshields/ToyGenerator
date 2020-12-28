#include "tupling.h"

void Tupling::operator()(Event& ev)
{
  if ( !ev.Accept ) return;
  //ev.updateMasses();

  Param* param = head;
  while ( param != nullptr ) {
    param->operator()(ev);
    param = param->next;
  }
  
  return;
}

void Tupling::addParam(Param& param)
{
  m_variables.push_back( std::move(param) );
  addParamToList(m_variables[m_variables.size()-1]);
}

void Tupling::addParam(Param* param)
{
  m_variables.push_back( std::move(*param) );
  addParamToList(m_variables[m_variables.size()-1]);
}

void Tupling::addParamToList(Param* param)
{
  Param* tmp = nullptr;
  tmp = param;
  tmp->next=nullptr;
  if ( head == nullptr ) {
    head=tmp;
    tail=tmp;
    tmp=nullptr;
  } else {
    tail->next=tmp;
    tail=tmp;
  }
  return;
}

void Tupling::addMomentum()
{
  std::vector<std::string> mvars = {"Px","Py","Pz","Pt","P"};
  for (int i = 1; i < gDescriptor.getParticles().size(); i++) {
    for (auto& var : mvars) {
      std::string name = "_"+std::to_string(i)+"_"+gDescriptor.getParticles()[i]+"_"+var+"_";
      m_variables.push_back( Param(name,var,i) );
      addParamToList(m_variables[m_variables.size()-1]);
    }
  }
}

void Tupling::addCharge()
{
  for (int i = 1; i < gDescriptor.getParticles().size(); i++) {
    std::string name = "_"+std::to_string(i)+"_"+gDescriptor.getParticles()[i]+"_Q_";
    m_variables.push_back( Param(name,"Q",i) );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::printParams()
{
  std::string param_str = "Params = ";
  Param* tmp = nullptr;
  tmp = head;
  while ( tmp != NULL ){
    param_str += tmp->name()+", ";
		tmp=tmp->next;
	}
  param_str.replace(param_str.size()-2,2,"");
  INFO(param_str);
  return;
}