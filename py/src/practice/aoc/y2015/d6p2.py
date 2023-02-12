# Day 6, Part Two

# You just finish implementing your winning light pattern when you
# realize you mistranslated Santa's message from Ancient Nordic
# Elvish.

# The light grid you bought actually has individual brightness
# controls; each light can have a brightness of zero or more. The
# lights all start at zero.

# The phrase turn on actually means that you should increase the
# brightness of those lights by 1.

# The phrase turn off actually means that you should decrease the
# brightness of those lights by 1, to a minimum of zero.

# The phrase toggle actually means that you should increase the
# brightness of those lights by 2.

# What is the total brightness of all lights combined after following
# Santa's instructions?

# For example:

# turn on 0,0 through 0,0 would increase the total brightness by 1.

# toggle 0,0 through 999,999 would increase the total brightness by
# 2000000.

from typing import List

import practice.aoc.y2015.d6 as d6


Row = List[int]
Grid = List[Row]


def make_grid() -> Grid:
    return [([0] * d6.SIZE) for x in range(d6.SIZE)]


def process(instruction: d6.Instruction, grid: Grid) -> None:
    for i in range(instruction.src.i, instruction.dst.i + 1):
        for j in range(instruction.src.j, instruction.dst.j + 1):
            if instruction.command == d6.Command.ON:
                grid[i][j] += 1
            elif instruction.command == d6.Command.OFF:
                if grid[i][j] > 0:
                    grid[i][j] -= 1
            elif instruction.command == d6.Command.TOGGLE:
                grid[i][j] += 2


def brightness(grid: Grid) -> int:
    value: int = 0
    for i in range(d6.SIZE):
        for j in range(d6.SIZE):
            value += grid[i][j]
    return value
