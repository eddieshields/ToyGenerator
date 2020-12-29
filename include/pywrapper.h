#ifndef TOYGEN_PYWRAPPER_H
#define TOYGEN_PYWRAPPER_H

#include <Python/Python.h>

class CPyInstance
{
public:
	CPyInstance()
	{
		Py_Initialize();
	}

	~CPyInstance()
	{
		Py_Finalize();
	}
};


class PyWrapper
{
private:
	PyObject *p;
public:
  PyWrapper() : p(NULL)
  {}
  PyWrapper(PyObject* _p) : p(_p)
  {}
  ~PyWrapper()
  {
  	Release();
  }

  PyObject* getObject() { return p; }
  PyObject* setObject(PyObject* _p) { return ( p = _p ); }

  PyObject* AddRef();
  void Release();
  PyObject* operator ->() { return p; }
  bool is() { return p ? true : false; }
  operator PyObject*() { return p; }
  PyObject* operator = (PyObject* pp);
  operator bool() { return p ? true : false; }

  void operator()(PyObject* ev)
  {
    //PyObject_CallObject(p, ev);
  }

};


#endif