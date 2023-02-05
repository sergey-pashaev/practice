import unittest

from aoc.y2015.d1p1 import what_floor
from aoc.y2015.d1p2 import at_basement


class Test(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(what_floor("(())"), 0)
        self.assertEqual(what_floor("()()"), 0)
        self.assertEqual(what_floor("((("), 3)
        self.assertEqual(what_floor("(()(()("), 3)
        self.assertEqual(what_floor("))((((("), 3)
        self.assertEqual(what_floor("())"), -1)
        self.assertEqual(what_floor("))("), -1)
        self.assertEqual(what_floor(")))"), -3)
        self.assertEqual(what_floor(")())())"), -3)

    def test_part_2(self):
        self.assertEqual(at_basement(")"), 1)
        self.assertEqual(at_basement("()())"), 5)

    def test_input(self):
        with open("tests/y2015/d1.input", "r") as f:
            for line in f.readlines():
                print()
                print("part 1:", what_floor(line))
                print("part 2:", at_basement(line))
