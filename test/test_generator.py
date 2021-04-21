from hydra import *

import unittest

class TestGenerator(unittest.TestCase):

    def test_generator(self):
        gDescriptor("D0 => K_S0 K+ K-")
        gen = Generator("Generator")

        ev = Event()
        gen( ev )

        self.assertIsNot( ev.mother().time() , 0 )
        self.assertEqual( ev.particles().size() , 4 )