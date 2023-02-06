# Day 5, Part One

# Santa needs help figuring out which strings in his text file are
# naughty or nice.

# A nice string is one with all of the following properties:

# It contains at least three vowels (aeiou only), like aei, xazegov,
# or aeiouaeiouaeiou.

# It contains at least one letter that appears twice in a row, like
# xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).

# It does not contain the strings ab, cd, pq, or xy, even if they are
# part of one of the other requirements.

# For example:

# ugknbfddgicrmopn is nice because it has at least three vowels
# (u...i...o...), a double letter (...dd...), and none of the
# disallowed substrings.

# aaa is nice because it has at least three vowels and a double
# letter, even though the letters used by different rules overlap.

# jchzalrnumimnmhp is naughty because it has no double letter.

# haegwjzuvuyypxyu is naughty because it contains the string xy.

# dvszwmarrgswjxmb is naughty because it contains only one vowel.

from typing import List


FORBIDDEN: List[str] = ["ab", "cd", "pq", "xy"]
VOWELS: List[str] = ["a", "e", "i", "o", "u"]


def is_nice(string: str) -> int:
    vowels: int = 0
    twice: bool = False
    has_forbidden: bool = False

    n: int = len(string)
    for i, char in enumerate(string):
        vowels += int(char in VOWELS)
        if i + 1 < n:
            if string[i + 1] == char:
                twice = True

            pair = char + string[i + 1]
            if pair in FORBIDDEN:
                has_forbidden = True

    return not has_forbidden and (vowels >= 3 and twice)
