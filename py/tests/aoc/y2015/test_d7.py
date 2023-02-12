import unittest

import practice.aoc.y2015.d7 as d7


class Test(unittest.TestCase):
    def test_input(self):
        with open("tests/aoc/y2015/d7.input", "r") as f:
            wires: d7.Wires = dict()
            for line in f.readlines():
                line = line[:-1]  # cut trailing \n
                tokens = d7.tokenize(line)
                output_wire = tokens.pop()
                wires[output_wire.operand.wire] = d7.Wire(tokens=tokens)

            a_part_1: int = d7.wire_eval("a", wires)
            for name, wire in wires.items():
                # invalidate cached values
                wire.value = -1

                # reset all signals
                tokens = wire.tokens
                if len(tokens) == 1 and tokens[0].type == d7.TokenType.NUMBER:
                    tokens[0].operand.number = 0

            # override b to a
            wires["b"].tokens[0].operand.number = a_part_1
            a_part_2: int = d7.wire_eval("a", wires)

            print()
            print("Day 7, part 1:", a_part_1)
            print("Day 7, part 2:", a_part_2)
