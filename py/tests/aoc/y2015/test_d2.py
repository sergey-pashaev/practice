import unittest

from practice.aoc.y2015.d2p1 import surface
from practice.aoc.y2015.d2p2 import ribbon


class Test(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(surface(""), 0)
        self.assertEqual(surface("2x3x4"), 58)
        self.assertEqual(surface("1x1x10"), 43)

    def test_part_2(self):
        self.assertEqual(ribbon(""), 0)
        self.assertEqual(ribbon("2x3x4"), 34)
        self.assertEqual(ribbon("1x1x10"), 14)

    def test_input(self):
        with open("tests/aoc/y2015/d2.input", "r") as f:
            surface_total = 0
            ribbon_total = 0
            for line in f.readlines():
                surface_total += surface(line)
                ribbon_total += ribbon(line)
            print()
            print("Day 2, part 1:", surface_total)
            print("Day 2, part 2:", ribbon_total)
