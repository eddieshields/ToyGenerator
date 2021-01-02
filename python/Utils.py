import ROOT as r
r.gSystem.Load('build/libHYDRA')

from numba import jit

class PyAlgorithm(r.PyAlgorithm):
    def __init__(self,name,func):
        self.m_func = func
        r.PyAlgorithm( name , func )

    @jit(nogil=True)
    def __call__(ev):
        self,m_func(ev)