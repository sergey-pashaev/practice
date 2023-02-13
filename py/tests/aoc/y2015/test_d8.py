import unittest

from practice.aoc.y2015.d8p1 import count as count_part_1
from practice.aoc.y2015.d8p2 import count as count_part_2


class Test(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(count_part_1('""'), (2, 0))
        self.assertEqual(count_part_1('"abc"'), (5, 3))
        self.assertEqual(count_part_1('"aaa\\"aaa"'), (10, 7))
        self.assertEqual(count_part_1('"\\x27"'), (6, 1))

    def test_part_2(self):
        self.assertEqual(count_part_2('""'), (6, 0))
        self.assertEqual(count_part_2('"abc"'), (9, 3))
        self.assertEqual(count_part_2('"aaa\\"aaa"'), (16, 7))
        self.assertEqual(count_part_2('"\\x27"'), (11, 1))

    def test_input(self):
        with open("tests/aoc/y2015/d8.input", "r") as f:
            code_raw: int = 0
            code_enc: int = 0
            mem: int = 0
            for line in f.readlines():
                line = line[:-1]  # cut trailing \n
                ret_raw = count_part_1(line)
                ret_enc = count_part_2(line)
                code_raw += ret_raw[0]
                code_enc += ret_enc[0]
                mem += ret_raw[1]
            part_1: int = code_raw - mem
            part_2: int = code_enc - code_raw
            print()
            print("Day 8, part 1:", part_1)
            print("Day 8, part 2:", part_2)
