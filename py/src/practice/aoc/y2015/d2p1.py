# Day 2, Part One

# The elves are running low on wrapping paper, and so they need to
# submit an order for more. They have a list of the dimensions
# (length l, width w, and height h) of each present, and only want to
# order exactly as much as they need.

# Fortunately, every present is a box (a perfect right rectangular
# prism), which makes calculating the required wrapping paper for
# each gift a little easier: find the surface area of the box, which
# is 2*l*w + 2*w*h + 2*h*l. The elves also need a little extra paper
# for each present: the area of the smallest side.

# For example:

# A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52
# square feet of wrapping paper plus 6 square feet of slack, for a
# total of 58 square feet.

# A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42
# square feet of wrapping paper plus 1 square foot of slack, for a
# total of 43 square feet.

# All numbers in the elves' list are in feet. How many total square
# feet of wrapping paper should they order?

from typing import List


def surface(string: str) -> int:
    parts = list(filter(lambda x: len(x) > 0, string.split("x")))
    if len(parts) != 3:
        return 0

    dimensions: List[int] = list(map(int, parts))
    sides = [
        dimensions[0] * dimensions[1],
        dimensions[1] * dimensions[2],
        dimensions[2] * dimensions[0],
    ]
    return 2 * sum(sides) + min(sides)
