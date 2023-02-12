import unittest

import practice.aoc.y2015.d6p1 as d6p1
import practice.aoc.y2015.d6p2 as d6p2
import practice.aoc.y2015.d6 as d6


class Test(unittest.TestCase):
    def test_input(self):
        with open("tests/aoc/y2015/d6.input", "r") as f:
            grid_p1: d6p1.Grid = d6p1.make_grid()
            grid_p2: d6p2.Grid = d6p2.make_grid()

            for line in f.readlines():
                line = line[:-1]  # cut trailing \n
                instruction = d6.read_instruction(line)
                d6p1.process(instruction, grid_p1)
                d6p2.process(instruction, grid_p2)
            print()
            print("Day 6, part 1:", d6p1.lights(grid_p1))
            print("Day 6, part 2:", d6p2.brightness(grid_p2))
