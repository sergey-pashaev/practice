# Day 2, Part Two

# The elves are also running low on ribbon. Ribbon is all the same
# width, so they only have to worry about the length they need to
# order, which they would again like to be exact.

# The ribbon required to wrap a present is the shortest distance
# around its sides, or the smallest perimeter of any one face. Each
# present also requires a bow made out of ribbon as well; the feet of
# ribbon required for the perfect bow is equal to the cubic feet of
# volume of the present. Don't ask how they tie the bow, though;
# they'll never tell.

# For example:

# A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of
# ribbon to wrap the present plus 2*3*4 = 24 feet of ribbon for the
# bow, for a total of 34 feet.

# A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of
# ribbon to wrap the present plus 1*1*10 = 10 feet of ribbon for the
# bow, for a total of 14 feet.

# How many total feet of ribbon should they order?

from typing import List
import math


def ribbon(string: str) -> int:
    parts = list(filter(lambda x: len(x) > 0, string.split("x")))
    if len(parts) != 3:
        return 0

    dimensions: List[int] = list(map(int, parts))
    perimeters: List[int] = [
        2 * (dimensions[0] + dimensions[1]),
        2 * (dimensions[1] + dimensions[2]),
        2 * (dimensions[2] + dimensions[0]),
    ]

    return min(perimeters) + math.prod(dimensions)
