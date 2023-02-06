import unittest

from practice.aoc.y2015.d5p1 import is_nice as is_nice_part_1
from practice.aoc.y2015.d5p2 import is_nice as is_nice_part_2


class Test(unittest.TestCase):
    def test_part_1(self):
        self.assertTrue(is_nice_part_1("ugknbfddgicrmopn"))
        self.assertTrue(is_nice_part_1("aaa"))
        self.assertFalse(is_nice_part_1("jchzalrnumimnmhp"))
        self.assertFalse(is_nice_part_1("haegwjzuvuyypxyu"))
        self.assertFalse(is_nice_part_1("dvszwmarrgswjxmb"))

    def test_part_2(self):
        self.assertTrue(is_nice_part_2("qjhvhtzxzqqjkmpb"))
        self.assertTrue(is_nice_part_2("xxyxx"))
        self.assertFalse(is_nice_part_2("uurcxstgmygtbstg"))
        self.assertFalse(is_nice_part_2("ieodomkazucvgmuy"))

    def test_input(self):
        with open("tests/aoc/y2015/d5.input", "r") as f:
            nice_part_1: int = 0
            nice_part_2: int = 0
            for line in f.readlines():
                line = line[:-1]  # cut trailing \n
                nice_part_1 += int(is_nice_part_1(line))
                nice_part_2 += int(is_nice_part_2(line))
            print()
            print("Day 5, part 1:", nice_part_1)
            print("Day 5, part 2:", nice_part_2)
