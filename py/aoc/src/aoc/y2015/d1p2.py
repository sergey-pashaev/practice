# Day 1, Part Two

# Now, given the same instructions, find the position of the first
# character that causes him to enter the basement (floor -1). The
# first character in the instructions has position 1, the second
# character has position 2, and so on.

# For example:

#   ) causes him to enter the basement at character position 1.
#   ()()) causes him to enter the basement at character position 5.

# What is the position of the character that causes Santa to first
# enter the basement?

def at_basement(string: str) -> int:
    floor: int = 0
    pos: int = 0
    for char in string:
        pos += 1
        if char == "(":
            floor += 1
        elif char == ")":
            floor -= 1
        elif char == "\n":
            return pos
        else:
            raise Exception("bad input: %c" % char)

        if floor == -1:
            return pos
    return 0
