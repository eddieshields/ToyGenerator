#include "pywrapper.h"

PyObject* PyWrapper::AddRef()
{
  if(p)
  {
  	Py_INCREF(p);
  }
  return p;
}
void PyWrapper::Release()
{
  if(p)
  {
  	Py_DECREF(p);
  }
  p= NULL;
}

PyObject* PyWrapper::operator = (PyObject* pp)
{
  p = pp;
  return p;
}
