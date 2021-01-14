#ifndef TOYGEN_CORRELATIONUTILS_H
#define TOYGEN_CORRELATIONUTILS_H

#include "msgservice.h"

#include <stdlib.h>
#include <map>
#include <string>

#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "Rtypes.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooMultiVarGaussian.h"


struct CorrelationUtils
{
  static TF1* VaryFunction(TF1* function, TFitResultPtr* resultptr);
  static TF1* VaryFunction(TF1* function, TFitResult* result);
  static std::vector<double> VaryWithinErrors(std::vector<double>& params, std::vector<double>& errors, TMatrixDSym& cov);

  static TMatrixDSym CalculateCovMatrix(std::vector<double>& errors, TMatrixDSym& corr);

  struct CovarianceMatrix
  {
    CovarianceMatrix() = default;
    CovarianceMatrix(std::vector<std::string> params, TMatrixDSym cov) :
      m_names( params ),
      m_cov( cov )
    {
      for (int i = 0; i < params.size(); i++) {
        m_params[params[i]] = 1;
      }
    }
    ~CovarianceMatrix() {}

    std::vector<std::string> names() { return m_names; }

    TMatrixDSym& operator()() { return m_cov; }
    double       operator()(int& i, int& j);
    double       operator()(std::string& name1, std::string& name2);

    std::vector<std::string>  m_names;
    std::map<std::string,int> m_params;
    TMatrixDSym               m_cov;
  };
};

#endif