from hydra import *

import unittest

class TestDescriptor(unittest.TestCase):

    def test_size(self):
        descriptor = DecayDescriptor()
        descriptor("D0 => K_S0 K+ K-")
        self.assertEqual( descriptor.getParticles().size() , 4 )

    def test_charges(self):
        descriptor = DecayDescriptor()
        descriptor("D0 => K_S0 K+ K-")
        self.assertEqual( descriptor.getCharges()[0] , 0 )
        self.assertEqual( descriptor.getCharges()[1] , 0 )
        self.assertEqual( descriptor.getCharges()[2] , +1 )
        self.assertEqual( descriptor.getCharges()[3] , -1 )