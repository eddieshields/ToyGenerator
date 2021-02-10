#ifndef TOYGEN_CONFIGFILE_H
#define TOYGEN_CONFIGFILE_H

#include "correlationutils.h"
#include "msgservice.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iterator>  

namespace DalitzModel {

class ConfigFile
{
public:
  enum Section {
    None,
    Resonances,
    Parameters,
    CorrelationMatrix,
    CovarianceMatrix,
  };
  ConfigFile(const std::string cfgfile );
  ~ConfigFile() {}

  std::map<std::string,std::vector<std::string>> resonances() { return m_resonances; }
  std::map<std::string,std::vector<std::string>> parameters() { return m_parameters; }

  // Get Resonances and Parameters.
  bool find(std::string entry);
  std::vector<std::string> operator[](std::string entry);

  // Get Correlation and Covariance.
  bool existsCorrelationMatrix() { if ( m_correlation.size() ) return true; return false; }
  bool existsCovarianceMatrix()  { if ( m_covariance.size()  ) return true; return false; }

  CorrelationUtils::CorrelationMatrix Correlation();
  CorrelationUtils::CovarianceMatrix  Covariance();


private:
  std::map<std::string,std::vector<std::string>> m_resonances;
  std::map<std::string,std::vector<std::string>> m_parameters;
  std::map<std::string,std::vector<std::string>> m_correlation;
  std::map<std::string,std::vector<std::string>> m_covariance;

  std::vector<std::string> m_cor_names;
  TMatrixDSym m_cor;

  std::vector<std::string> m_cov_names;
  TMatrixDSym m_cov;

  void decodeResonances(std::string line);
  void decodeParameters(std::string line);
  void decodeCorrelationMatrix(std::string line);
  void decodeCovarianceMatrix(std::string line);
};

}

#endif