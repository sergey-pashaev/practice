# Day 6, Part One

# Because your neighbors keep defeating you in the holiday house
# decorating contest year after year, you've decided to deploy one
# million lights in a 1000x1000 grid.

# Furthermore, because you've been especially nice this year, Santa
# has mailed you instructions on how to display the ideal lighting
# configuration.

# Lights in your grid are numbered from 0 to 999 in each direction;
# the lights at each corner are at 0,0, 0,999, 999,999, and
# 999,0. The instructions include whether to turn on, turn off, or
# toggle various inclusive ranges given as coordinate pairs. Each
# coordinate pair represents opposite corners of a rectangle,
# inclusive; a coordinate pair like 0,0 through 2,2 therefore refers
# to 9 lights in a 3x3 square. The lights all start turned off.

# To defeat your neighbors this year, all you have to do is set up
# your lights by doing the instructions Santa sent you in order.

# For example:

# turn on 0,0 through 999,999 would turn on (or leave on) every
# light.

# toggle 0,0 through 999,0 would toggle the first line of 1000
# lights, turning off the ones that were on, and turning on the ones
# that were off.

# turn off 499,499 through 500,500 would turn off (or leave off) the
# middle four lights.

# After following the instructions, how many lights are lit?

from typing import List

import practice.aoc.y2015.d6 as d6


Row = List[bool]
Grid = List[Row]


def make_grid() -> Grid:
    return [([False] * d6.SIZE) for x in range(d6.SIZE)]


def process(instruction: d6.Instruction, grid: Grid) -> None:
    for i in range(instruction.src.i, instruction.dst.i + 1):
        for j in range(instruction.src.j, instruction.dst.j + 1):
            if instruction.command == d6.Command.ON:
                grid[i][j] = True
            elif instruction.command == d6.Command.OFF:
                grid[i][j] = False
            elif instruction.command == d6.Command.TOGGLE:
                grid[i][j] = not grid[i][j]


def lights(grid: Grid) -> int:
    lit: int = 0
    for i in range(d6.SIZE):
        for j in range(d6.SIZE):
            if grid[i][j]:
                lit += 1
    return lit
