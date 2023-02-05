# Day 3, Part Two

# The next year, to speed up the process, Santa creates a robot
# version of himself, Robo-Santa, to deliver presents with him.

# Santa and Robo-Santa start at the same location (delivering two
# presents to the same starting house), then take turns moving based
# on instructions from the elf, who is eggnoggedly reading from the
# same script as the previous year.

# This year, how many houses receive at least one present?

# For example:

# ^v delivers presents to 3 houses, because Santa goes north, and
# then Robo-Santa goes south.

# ^>v< now delivers presents to 3 houses, and Santa and Robo-Santa
# end up back where they started.

# ^v^v^v^v^v now delivers presents to 11 houses, with Santa going one
# direction and Robo-Santa going the other.

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
    santa = Position()
    robot = Position()

    houses: Set[Position] = set()
    houses.add(santa)
    houses.add(robot)

    i = iter(string)
    direction = next(i, None)
    while direction is not None:
        santa.move(direction)
        houses.add(copy(santa))

        direction = next(i, None)
        if direction is not None:
            robot.move(direction)
            houses.add(copy(robot))
            direction = next(i, None)

    return len(houses)
