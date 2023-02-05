# Day 3, Part One

# Santa is delivering presents to an infinite two-dimensional grid of
# houses.

# He begins by delivering a present to the house at his starting
# location, and then an elf at the North Pole calls him via radio and
# tells him where to move next. Moves are always exactly one house to
# the north (^), south (v), east (>), or west (<). After each move,
# he delivers another present to the house at his new location.

# However, the elf back at the north pole has had a little too much
# eggnog, and so his directions are a little off, and Santa ends up
# visiting some houses more than once. How many houses receive at
# least one present?

# For example:

# > delivers presents to 2 houses: one at the starting location, and
# > one to the east.

# ^>v< delivers presents to 4 houses in a square, including twice to
# the house at his starting/ending location.

# ^v^v^v^v^v delivers a bunch of presents to some very lucky children
# at only 2 houses.

from dataclasses import dataclass
from typing import Set
from copy import copy


@dataclass(unsafe_hash=True)
class Position:
    x: int = 0
    y: int = 0

    def move(self, direction: str) -> None:
        if direction == ">":
            self.x += 1
        elif direction == "<":
            self.x -= 1
        elif direction == "^":
            self.y += 1
        elif direction == "v":
            self.y -= 1
        else:
            raise Exception("bad input: %s" % direction)


def delivery(string: str) -> int:
    position = Position()
    houses: Set[Position] = set()
    houses.add(position)

    for direction in string:
        position.move(direction)
        houses.add(copy(position))

    return len(houses)
