# Day 8, Part Two

# Now, let's go the other way. In addition to finding the number of
# characters of code, you should now encode each code representation
# as a new string and find the number of characters of the new
# encoded representation, including the surrounding double quotes.

# For example:

# "" encodes to "\"\"", an increase from 2 characters to 6.

# "abc" encodes to "\"abc\"", an increase from 5 characters to 9.

# "aaa\"aaa" encodes to "\"aaa\\\"aaa\"", an increase from 10 characters to 16.

# "\x27" encodes to "\"\\x27\"", an increase from 6 characters to 11.

# Your task is to find the total number of characters to represent
# the newly encoded strings minus the number of characters of code in
# each original string literal. For example, for the strings above,
# the total encoded length (6 + 9 + 16 + 11 = 42) minus the
# characters in the original code representation (23, just like in
# the first part of this puzzle) is 42 - 23 = 19.

import string

from typing import Tuple


def is_hex(char: str) -> bool:
    assert len(char) == 1
    return char in string.hexdigits


def count(s: str, encoded: bool = True) -> Tuple[int, int]:
    code: int = 0
    mem: int = 0

    n: int = len(s)
    i: int = 0
    while i < n:
        if s[i] == '"':
            # quote
            code += 3 if encoded else 1
            i += 1
        elif s[i] == '\\':
            if s[i + 1] == '\\' or s[i + 1] == '"':
                # backslash or quoted quote
                i += 2
                code += 4 if encoded else 2
                mem += 1
            elif s[i + 1] == "x" and is_hex(s[i + 2]) and is_hex(s[i + 3]):
                # hex
                i += 4
                code += 5 if encoded else 4
                mem += 1
        else:
            # regular character
            i += 1
            code += 1
            mem += 1

    return (code, mem)
