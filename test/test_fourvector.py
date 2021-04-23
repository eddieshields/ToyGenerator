from hydra import *
import math

import unittest

class TestFourVector(unittest.TestCase):
    def test_addition(self):
        v1 = FourVector(1,1,1,1)
        v2 = FourVector(2,2,2,2)
        v3 = v1 + v2
        self.assertEqual( v3.X()  == 3 )
        self.assertEqual( v3.Y()  == 3 )
        self.assertEqual( v3.Z()  == 3 )
        self.assertEqual( v3.T()  == 3 )
        self.assertEqual( v3.Px() == 3 )
        self.assertEqual( v3.Py() == 3 )
        self.assertEqual( v3.Pz() == 3 )
        self.assertEqual( v3.E()  == 3 )

    def test_subtraction(self):
        v1 = FourVector(1,1,1,1)
        v2 = FourVector(2,2,2,2)
        v4 = v2 - v1
        self.assertEqual( v4.X()  == 1 )
        self.assertEqual( v4.Y()  == 1 )
        self.assertEqual( v4.Z()  == 1 )
        self.assertEqual( v4.T()  == 1 )
        self.assertEqual( v4.Px() == 1 )
        self.assertEqual( v4.Py() == 1 )
        self.assertEqual( v4.Pz() == 1 )
        self.assertEqual( v4.E()  == 1 )

    def test_multiplication(self):
        v1 = FourVector(1,1,1,1)
        v2 = FourVector(2,2,2,2)
        v5 = v1 * v2
        self.assertEqual( v5 == 8 )

    def test_addto(self):
        v1 = FourVector(1,1,1,1)
        v6 = FourVector(3,3,3,3)
        v6 += v1
        self.assertEqual( v6.X()  == 4 )
        self.assertEqual( v6.Y()  == 4 )
        self.assertEqual( v6.Z()  == 4 )
        self.assertEqual( v6.T()  == 4 )
        self.assertEqual( v6.Px() == 4 )
        self.assertEqual( v6.Py() == 4 )
        self.assertEqual( v6.Pz() == 4 )
        self.assertEqual( v6.E()  == 4 )

    def test_methods(self):
        v7 = FourVector(1,2,3,4)
        self.assertEqual( v7.P()    == math.sqrt(14) )
        self.assertEqual( v7.Pt()   == math.sqrt(5) )
        self.assertEqual( v7.M()    == math.sqrt(2) )
        self.assertEqual( v7.M2()   == 2 )
        self.assertEqual( v7.Mag()  == math.sqrt(2) )
        self.assertEqual( v7.Mag2() == 2 )

    def test_setters(self):
        v8 = FourVector(1,1,1,1)
        v8.SetXYZT(2,2,2,2)
        self.assertEqual( v8.X()  == 2 )
        self.assertEqual( v8.Y()  == 2 )
        self.assertEqual( v8.Z()  == 2 )
        self.assertEqual( v8.T()  == 2 )
        self.assertEqual( v8.Px() == 2 )
        self.assertEqual( v8.Py() == 2 )
        self.assertEqual( v8.Pz() == 2 )
        self.assertEqual( v8.E()  == 2 )
        v8.SetPxPyPzE(3,3,3,3)
        self.assertEqual( v8.X()  == 3 )
        self.assertEqual( v8.Y()  == 3 )
        self.assertEqual( v8.Z()  == 3 )
        self.assertEqual( v8.T()  == 3 )
        self.assertEqual( v8.Px() == 3 )
        self.assertEqual( v8.Py() == 3 )
        self.assertEqual( v8.Pz() == 3 )
        self.assertEqual( v8.E()  == 3 )

    def test_indices(self):
        v1 = FourVector(1,1,1,1)
        self.assertEqual( v1[0] == 1 )
        self.assertEqual( v1[1] == 1 )
        self.assertEqual( v1[2] == 1 )
        self.assertEqual( v1[3] == 1 )
        self.assertEqual( v1(0) == 1 )
        self.assertEqual( v1(1) == 1 )
        self.assertEqual( v1(2) == 1 )
        self.assertEqual( v1(3) == 1 )


