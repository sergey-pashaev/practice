#!/usr/bin/env python

# ex.5

# cons(a, b) constructs a pair, and car(pair) and cdr(pair) returns
# the first and last element of that pair. For example, car(cons(3,
# 4)) returns 3, and cdr(cons(3, 4)) returns 4.

# Given this implementation of cons:

# def cons(a, b):
#     def pair(f):
#         return f(a, b)
#     return pair
# Implement car and cdr.

import unittest

def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair

def car(pair):
    return pair(lambda a, b:  a)

def cdr(pair):
    return pair(lambda a, b: b)

class Test(unittest.TestCase):
    def test_car(self):
        self.assertEqual(car(cons(3, 4)), 3)
        self.assertEqual(car(car(cons(cons(1, 2), 4))), 1)

    def test_cdr(self):
        self.assertEqual(cdr(cons(3, 4)), 4)
        self.assertEqual(cdr(car(cons(cons(1, 2), 4))), 2)

if __name__ == '__main__':
    unittest.main()
