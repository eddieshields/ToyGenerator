#include "tupling.h"

void Tupling::operator()(Event& ev)
{
  if ( !ev.Accept ) return;
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
  for (int i = 1; i < gDescriptor.getCleanParticles().size(); i++) {
    std::string name_px = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_Px_";
    Param* param_px = new ParticleParam<Param::PX>(name_px,"Px",i);
    m_variables.push_back( param_px );
    addParamToList(m_variables[m_variables.size()-1]);
      
    std::string name_py = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_Py_";
    Param* param_py = new ParticleParam<Param::PY>(name_px,"Py",i);
    m_variables.push_back( param_py );
    addParamToList(m_variables[m_variables.size()-1]);

    std::string name_pz = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_Pz_";
    Param* param_pz = new ParticleParam<Param::PZ>(name_pz,"Pz",i);
    m_variables.push_back( param_px );
    addParamToList(m_variables[m_variables.size()-1]);

    std::string name_pt = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_Pt_";
    Param* param_pt = new ParticleParam<Param::PT>(name_pt,"Pt",i);
    m_variables.push_back( param_pt );
    addParamToList(m_variables[m_variables.size()-1]);

    std::string name_p = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_P_";
    Param* param_p = new ParticleParam<Param::P>(name_p,"P",i);
    m_variables.push_back( param_p );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::addMass()
{
  std::map<std::string,Param::Type> mvars = {{"M",Param::M},{"MSq",Param::MSq}};
  for (int i = 1; i < gDescriptor.getCleanParticles().size(); i++) {
    std::string name_m = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_M_";
    Param* param_m = new ParticleParam<Param::M>(name_m,"M",i);
    m_variables.push_back( param_m );
    addParamToList(m_variables[m_variables.size()-1]);

    std::string name_msq = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_MSq_";
    Param* param_msq = new ParticleParam<Param::MSq>(name_msq,"MSq",i);
    m_variables.push_back( param_msq );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::addTime()
{
  std::string name = "_0_"+gDescriptor.getCleanParticles()[0]+"_T_";
  Param* param = new ParticleParam<Param::T>(name,"t",0);
  m_variables.push_back( param );
  addParamToList(m_variables[m_variables.size()-1]);
}

void Tupling::addCharge()
{
  for (int i = 1; i < gDescriptor.getCleanParticles().size(); i++) {
    std::string name = "_"+std::to_string(i)+"_"+gDescriptor.getCleanParticles()[i]+"_Q_";
    Param* param = new ParticleParam<Param::Q>(name,"Q",i);
    m_variables.push_back( param );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::addEventInfo()
{
  std::string name_w = "_weight_";
  Param* param_w = new EventParam<Param::W>(name_w,"w");
  m_variables.push_back( param_w );
  addParamToList(m_variables[m_variables.size()-1]);

  std::string name_p = "_pdf_";
  Param* param_p = new EventParam<Param::PDF>(name_p,"pdf");
  m_variables.push_back( param_p );
  addParamToList(m_variables[m_variables.size()-1]);
}

void Tupling::addCompositeMass()
{
  for (int i = 1; i < gDescriptor.getCleanParticles().size(); i++) {
    for (int j = i+1; j < gDescriptor.getCleanParticles().size(); j++) {
      std::string name_m = "_"+std::to_string(i)+std::to_string(j)+"_"+gDescriptor.getCleanParticles()[i]+gDescriptor.getCleanParticles()[j]+"_M_";
      Param* param_m = new CompositeParam<Param::M>(name_m,"M",i,j);
      m_variables.push_back( param_m );
      addParamToList(m_variables[m_variables.size()-1]);
      
      std::string name_msq = "_"+std::to_string(i)+std::to_string(j)+"_"+gDescriptor.getCleanParticles()[i]+gDescriptor.getCleanParticles()[j]+"_MSq_";
      Param* param_msq = new CompositeParam<Param::MSq>(name_msq,"MSq",i,j);
      m_variables.push_back( param_msq );
      addParamToList(m_variables[m_variables.size()-1]);
    }
  }
}

void Tupling::addCompositeMass(int index1, int index2)
{
  std::map<std::string,Param::Type> mvars = {{"M",Param::M},{"MSq",Param::MSq}};
  for (const auto& var : mvars) {
    std::string name_m = "_"+std::to_string(index1)+std::to_string(index2)+"_"+gDescriptor.getCleanParticles()[index1]+gDescriptor.getCleanParticles()[index2]+"_M_";
    Param* param_m = new CompositeParam<Param::M>(name_m,"M",index1,index2);
    m_variables.push_back( param_m );
    addParamToList(m_variables[m_variables.size()-1]);

    std::string name_msq = "_"+std::to_string(index1)+std::to_string(index2)+"_"+gDescriptor.getCleanParticles()[index1]+gDescriptor.getCleanParticles()[index2]+"_MSq_";
    Param* param_msq = new CompositeParam<Param::MSq>(name_msq,"MSq",index1,index2);
    m_variables.push_back( param_msq );
    addParamToList(m_variables[m_variables.size()-1]);
  }
}

void Tupling::addPID()
{
  std::string name = "_"+std::to_string(0)+"_"+gDescriptor.getCleanParticles()[0]+"_pid_";
  Param* param = new ParticleParam<Param::PID>(name,"PID",0);
  m_variables.push_back( param );
  addParamToList(m_variables[m_variables.size()-1]);
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