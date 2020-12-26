import ROOT as r 

r.gSystem.Load('build/libHYDRA')

# Wrapper class for C++ Hydra class.
class Hydra:
    def __init__(self):
        self.hy = r.Hydra()

    def __call__(self):
        return self.hy.m_configuration

    def run(self):
        self.hy.run()


    


