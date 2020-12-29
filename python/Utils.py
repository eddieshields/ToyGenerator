import ROOT as r
r.gSystem.Load('build/libHYDRA')

from numba import jit

# A helper structure that wraps around a function and uses 
# Just In Time compilation from numba to speed it up.
class PyAlg:
    def __init__(self,_func):
        self.func = _func

    @jit
    def __call__(self,ev):
        func(ev)