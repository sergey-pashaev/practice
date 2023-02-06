import unittest

from practice.aoc.y2015.d4p1 import crack as crack_part_1
from practice.aoc.y2015.d4p2 import crack as crack_part_2


class Test(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(crack_part_1("abcdef"), 609043)
        self.assertEqual(crack_part_1("pqrstuv"), 1048970)

    def test_input(self):
        with open("tests/aoc/y2015/d4.input", "r") as f:
            for line in f.readlines():
                line = line[:-1]  # cut trailing \n
                print()
                print("Day 4, part 1:", crack_part_1(line))
                print("Day 4, part 2:", crack_part_2(line))
