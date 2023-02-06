import unittest

from practice.aoc.y2015.d3p1 import delivery as delivery_part_1
from practice.aoc.y2015.d3p2 import delivery as delivery_part_2


class Test(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(delivery_part_1(""), 1)
        self.assertEqual(delivery_part_1(">"), 2)
        self.assertEqual(delivery_part_1("^>v<"), 4)
        self.assertEqual(delivery_part_1("^v^v^v^v^v"), 2)

    def test_part_2(self):
        self.assertEqual(delivery_part_2(""), 1)
        self.assertEqual(delivery_part_2("^v"), 3)
        self.assertEqual(delivery_part_2("^>v<"), 3)
        self.assertEqual(delivery_part_2("^v^v^v^v^v"), 11)

    def test_input(self):
        with open("tests/aoc/y2015/d3.input", "r") as f:
            for line in f.readlines():
                line = line[:-1]  # cut trailing \n
                print()
                print("Day 3, part 1:", delivery_part_1(line))
                print("Day 3, part 2:", delivery_part_2(line))
