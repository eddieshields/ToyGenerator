from hydra import *
import time

import unittest

class TestClock(unittest.TestCase):
    def test_clock(self):
        Clock.Start()
        time.sleep(1)
        Clock.Stop()
        Clock.Print("test clock works")