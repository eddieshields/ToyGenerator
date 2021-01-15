#include "configfile.h"

using namespace DalitzModel;

ConfigFile::ConfigFile(const std::string cfgfile)
{
  std::ifstream ifs(cfgfile);
  std::string line;
  ConfigFile::Section section = ConfigFile::None;
  while (std::getline(ifs, line)) {
    if (line.empty() || line.at(0) == '#') {
      continue;
    }

    // Move between sections.
    if ( line == "Resonances" ) {
      section = ConfigFile::Resonances; 
    } else if ( line == "Parameters" ) {
      section = ConfigFile::Parameters;
    } else if ( line == "CorrelationMatrix" ) {
      section = ConfigFile::CorrelationMatrix;
    } else if ( line == "CovarianceMatrix"  ) {
      section = ConfigFile::CovarianceMatrix;
    } else {
      switch (section)
      {
      case ConfigFile::Resonances:
        decodeResonances(line);
        continue;
      case ConfigFile::Parameters:
        decodeParameters(line);
        continue;
      case ConfigFile::CorrelationMatrix:
        decodeCorrelationMatrix(line);
        continue;
      case ConfigFile::CovarianceMatrix:
        decodeCovarianceMatrix(line);
        continue;
      default:
        continue;
      }
    }
  }
}

bool ConfigFile::find(std::string entry)
{
   if ( m_resonances.find(entry) != m_resonances.end() ) {
    return true;
  } else if ( m_parameters.find(entry) != m_parameters.end() ) {
    return true;
  }
  return false;
}

std::vector<std::string> ConfigFile::operator[](std::string entry)
{
  if ( m_resonances.find(entry) != m_resonances.end() ) {
    return m_resonances[entry];
  } else if ( m_parameters.find(entry) != m_parameters.end() ) {
    return m_parameters[entry];
  }
  WARNING("Couldn't find entry " << entry);
  return std::vector<std::string>{};
}

void ConfigFile::decodeResonances(std::string line)
{
  std::istringstream iss(line);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
  std::vector<std::string> associations;
  associations.insert(associations.end(),results.begin()+2,results.end());
  m_resonances[results[0]] = std::move( associations );
  return;
}

void ConfigFile::decodeParameters(std::string line)
{
  std::istringstream iss(line);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
  std::vector<std::string> associations;
  associations.insert(associations.end(),results.begin()+2,results.end());
  m_parameters[results[0]] = std::move( associations );
  return;
}

void ConfigFile::decodeCorrelationMatrix(std::string line)
{
  std::istringstream iss(line);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
  std::vector<std::string> associations;
  associations.insert(associations.end(),results.begin()+2,results.end());
  m_correlation[results[0]] = std::move( associations );

  // Resize matrix for first element.
  int size = m_correlation[results[0]].size();
  if ( m_correlation.size() == 1 ) {
    m_cor.ResizeTo( size , size );
  }

  m_cor_names.push_back( results[0] );
  int row = m_correlation.size() - 1;
  for (int i = 0; i < size; i++) {
    m_cor(row,i+row) = std::stod( m_correlation[results[0]][i] );
  } 

  return;
}

void ConfigFile::decodeCovarianceMatrix(std::string line)
{
  std::istringstream iss(line);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
  std::vector<std::string> associations;
  associations.insert(associations.end(),results.begin()+2,results.end());
  m_covariance[results[0]] = std::move( associations );
  
  // Resize matrix for first element.
  int size = m_covariance[results[0]].size();
  if ( m_correlation.size() == 1 ) {
    m_cov.ResizeTo( size , size );
  }

  m_cov_names.push_back( results[0] );
  int row = m_covariance.size() - 1;
  for (int i = 0; i < size; i++) {
    m_cov(row,i+row) = std::stod( m_covariance[results[0]][i] );
  } 

  return;
}

CorrelationUtils::CorrelationMatrix ConfigFile::Correlation()
{
  CorrelationUtils::CorrelationMatrix cor(m_cor_names,m_cor);
  return cor;
}

CorrelationUtils::CovarianceMatrix ConfigFile::Covariance()
{
  CorrelationUtils::CovarianceMatrix cov(m_cov_names,m_cov);
  return cov;
}