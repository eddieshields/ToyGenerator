import ROOT as r
r.gSystem.Load('build/libHYDRA')

from numba import jit
from numba.experimental import jitclass

# A helper structure that wraps around a function and uses 
# Just In Time compilation from numba to speed it up.
@jitclass
class FastAlgorithm:
    def __init__(self,_func):
        self.func = _func

    @staticmethod
    def __call__(self,ev):
        func(ev)