# Day 8, Part One

# Space on the sleigh is limited this year, and so Santa will be
# bringing his list as a digital copy. He needs to know how much
# space it will take up when stored.

# It is common in many programming languages to provide a way to
# escape special characters in strings. For example, C, JavaScript,
# Perl, Python, and even PHP handle special characters in very
# similar ways.

# However, it is important to realize the difference between the
# number of characters in the code representation of the string
# literal and the number of characters in the in-memory string
# itself.

# For example:

# "" is 2 characters of code (the two double quotes), but the string
# contains zero characters.

# "abc" is 5 characters of code, but 3 characters in the string data.

# "aaa\"aaa" is 10 characters of code, but the string itself contains
# six "a" characters and a single, escaped quote character, for a
# total of 7 characters in the string data.

# "\x27" is 6 characters of code, but the string itself contains just
# one - an apostrophe ('), escaped using hexadecimal notation.

# Santa's list is a file that contains many double-quoted string
# literals, one on each line. The only escape sequences used are \\
# (which represents a single backslash), \" (which represents a lone
# double-quote character), and \x plus two hexadecimal characters
# (which represents a single character with that ASCII code).

# Disregarding the whitespace in the file, what is the number of
# characters of code for string literals minus the number of
# characters in memory for the values of the strings in total for the
# entire file?

# For example, given the four strings above, the total number of
# characters of string code (2 + 5 + 10 + 6 = 23) minus the total
# number of characters in memory for string values (0 + 3 + 7 + 1 =
# 11) is 23 - 11 = 12.

import string

from typing import Tuple


def is_hex(char: str) -> bool:
    assert len(char) == 1
    return char in string.hexdigits


def count(s: str) -> Tuple[int, int]:
    code: int = 0
    mem: int = 0

    n: int = len(s)
    i: int = 0
    while i < n:
        if s[i] == '"':
            # quote
            code += 1
            i += 1
        elif s[i] == '\\':
            if s[i + 1] == '\\' or s[i + 1] == '"':
                # backslash or quoted quote
                i += 2
                code += 2
                mem += 1
            elif s[i + 1] == "x" and is_hex(s[i + 2]) and is_hex(s[i + 3]):
                # hex
                i += 4
                code += 4
                mem += 1
        else:
            # regular character
            i += 1
            code += 1
            mem += 1

    return (code, mem)
