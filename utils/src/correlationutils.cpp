#include "correlationutils.h"

TF1* CorrelationUtils::VaryFunction(TF1* function, TFitResultPtr* resultptr)
{
  TFitResult* result = resultptr->Get();
  return VaryFunction( function , result );
}

TF1* CorrelationUtils::VaryFunction(TF1* function, TFitResult* result)
{
  std::vector<double> params, errors;
  for (int i = 0; i < function->GetNpar(); i++) {
    params.push_back( result->Parameter(i) );
    errors.push_back( result->ParError(i) );
  }

  TMatrixDSym cov = result->GetCovarianceMatrix();
  
  std::vector<double> new_params = VaryWithinErrors(params,errors,cov);

  for (int i = 0; i < function->GetNpar(); i++) {
    function->FixParameter(i,new_params[i]);
  }
  return function;
}

std::vector<double> CorrelationUtils::VaryWithinErrors(std::vector<double>& params, std::vector<double>& errors, TMatrixDSym& cov)
{
  // Get the number of params.
  int npars = params.size();

  // Set up the vectors needed for RooMultiVarGaussian.
  RooArgList xVec;
  TVectorD   muVec(npars);
  RooRealVar* x;
  for (int i = 0; i < npars; i++) {
    char* name = Form("x%d", i);
    x = new RooRealVar(name,name,params[i]-10*errors[i],params[i]+10*errors[i]);
    xVec.add(*x);
    muVec[i] = params[i];
  }

  // Create RooMultiVarGaussian with covariance matrix.
  RooMultiVarGaussian mvg("mvg","mvg",xVec,muVec,cov);

  // Generate a value.
  RooDataSet* data = mvg.generate(xVec,1);
  // Get list.
  RooArgList* list = (RooArgList*)data->get(0);

  // Move values into new list;
  std::vector<double> out_params;
  out_params.resize( npars );
  for (int i = 0; i < npars; i++) {
    RooRealVar* p = (RooRealVar*)list->at(i);
    out_params[i] = p->getVal();
  }

  return out_params;
}

TMatrixDSym CorrelationUtils::CalculateCovMatrix(std::vector<double>& errors, TMatrixDSym& corr)
{
  int dim = errors.size();
  TMatrixDSym cov(dim);

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      cov(i,j) = corr(i,j) * errors[i] * errors[j];
    }
  }
  return cov;
}

double CorrelationUtils::CorrelationMatrix::operator()(int& i, int& j)
{
  return m_cor(i,j);
}

double CorrelationUtils::CorrelationMatrix::operator()(std::string& name1, std::string& name2)
{
  int i = m_params[name1];
  int j = m_params[name2];
  return m_cor(i,j);
}

double CorrelationUtils::CovarianceMatrix::operator()(int& i, int& j)
{
  return m_cov(i,j);
}

double CorrelationUtils::CovarianceMatrix::operator()(std::string& name1, std::string& name2)
{
  int i = m_params[name1];
  int j = m_params[name2];
  return m_cov(i,j);
}