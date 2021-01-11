#include "tupling.h"

void Tupling::operator()(Event& ev)
{
  if ( !ev.Accept ) continue;
  Param* param = nullptr;
  param = head;
  while ( param != nullptr ) {
    param->operator()(ev);
    param = param->next;
  }
  return;
}

void Tupling::addParam(Param& param)
{
  m_variables.push_back( std::move(static_cast<Param*>(&param)) );
  addParamToList(m_variables[m_variables.size()-1]);
}

void Tupling::addParam(Param* param)
{
  m_variables.push_back( std::move(static_cast<Param*>(param)) );
  addParamToList(m_variables[m_variables.size()-1]);
}

template <typename PARAM>
void Tupling::addParam(PARAM& param)
{ 
  // Add assertion.
  m_variables.push_back( std::move(static_cast<Param*>(&param)) );
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
      Param* param = new ParticleParam(name,var,i);
      m_variables.push_back( param );
      addParamToList(m_variables[m_variables.size()-1]);
    }
  }
}

void Tupling::addMass()
{
  std::vector<std::string> mvars = {"M","MSq"};
  for (int i = 1; i < gDescriptor.getParticles().size(); i++) {
    for (auto& var : mvars) {
      std::string name = "_"+std::to_string(i)+"_"+gDescriptor.getParticles()[i]+"_"+var+"_";
      Param* param = new ParticleParam(name,var,i);
      m_variables.push_back( param );
      addParamToList(m_variables[m_variables.size()-1]);
    }
  }
}

void Tupling::addTime()
{
  std::string name = "_0_"+gDescriptor.getParticles()[0]+"_T_";
  Param* param = new ParticleParam(name,"t",0);
  m_variables.push_back( param );
  addParamToList(m_variables[m_variables.size()-1]);
}

void Tupling::addCharge()
{
  for (int i = 1; i < gDescriptor.getParticles().size(); i++) {
    std::string name = "_"+std::to_string(i)+"_"+gDescriptor.getParticles()[i]+"_Q_";
    Param* param = new ParticleParam(name,"Q",i);
    m_variables.push_back( param );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::addEventInfo()
{
  std::vector<std::string> mvars = {"pdf","weight"};
  for (auto& var : mvars) {
    std::string name = "_"+var+"_";
    EventParam* param = new EventParam(name,var);
    m_variables.push_back( param );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::addCompositeMass()
{
  std::vector<std::string> mvars = {"M","MSq"};
  for (int i = 1; i < gDescriptor.getParticles().size(); i++) {
    for (int j = i+1; j < gDescriptor.getParticles().size(); j++) {
      for (auto& var : mvars) {
        std::string name = "_"+std::to_string(i)+std::to_string(j)+"_"+gDescriptor.getParticles()[i]+gDescriptor.getParticles()[j]+"_"+var+"_";
        CompositeParam* param = new CompositeParam(name,var,i,j);
        m_variables.push_back( param );
        addParamToList(m_variables[m_variables.size()-1]);
      }
    }
  }
}

void Tupling::addCompositeMass(int index1, int index2)
{
  std::vector<std::string> mvars = {"M","MSq"};
  for (auto& var : mvars) {
    std::string name = "_"+std::to_string(index1)+std::to_string(index2)+"_"+gDescriptor.getParticles()[index1]+gDescriptor.getParticles()[index2]+"_"+var+"_";
    CompositeParam* param = new CompositeParam(name,var,index1,index2);
    m_variables.push_back( param );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

std::vector<std::string> Tupling::getVariables()
{
  std::vector<std::string> names;
  for (auto& p : m_variables) {
    names.push_back( p->name() );
  }
  return names;
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