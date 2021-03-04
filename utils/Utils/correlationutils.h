#ifndef TOYGEN_CORRELATIONUTILS_H
#define TOYGEN_CORRELATIONUTILS_H

#include "msgservice.h"
#include "types.h"

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
  static std::vector<real_t> VaryWithinErrors(std::vector<real_t>& params, std::vector<real_t>& errors, TMatrixDSym& cov);

  static TMatrixDSym CalculateCovMatrix(std::vector<real_t>& errors, TMatrixDSym& corr);

  struct CorrelationMatrix
  {
    CorrelationMatrix() = default;
    CorrelationMatrix(std::vector<std::string> params, TMatrixDSym cor) :
      m_names( params ),
      m_cor( cor )
    {
      for (int i = 0; i < params.size(); i++) {
        m_params[params[i]] = 1;
      }
    }
    ~CorrelationMatrix() {}

    std::vector<std::string> names() { return m_names; }

    TMatrixDSym& matrix() { return m_cor; }
    TMatrixDSym& operator()() { return m_cor; }
    real_t       operator()(int& i, int& j);
    real_t       operator()(std::string& name1, std::string& name2);

    std::vector<std::string>  m_names;
    std::map<std::string,int> m_params;
    TMatrixDSym               m_cor;

  };

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

    TMatrixDSym& matrix() { return m_cov; }
    TMatrixDSym& operator()() { return m_cov; }
    real_t       operator()(int& i, int& j);
    real_t       operator()(std::string& name1, std::string& name2);

    std::vector<std::string>  m_names;
    std::map<std::string,int> m_params;
    TMatrixDSym               m_cov;
  };
};

#endif