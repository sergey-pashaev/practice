from typing import List, Dict, Tuple
from enum import Enum
from dataclasses import dataclass, field


class Operation(Enum):
    NONE = 1
    AND = 2
    OR = 3
    LSHIFT = 4
    RSHIFT = 5
    NOT = 6

    @staticmethod
    def from_string(token: str):
        if token == "AND":
            return Operation.AND
        elif token == "OR":
            return Operation.OR
        elif token == "LSHIFT":
            return Operation.LSHIFT
        elif token == "RSHIFT":
            return Operation.RSHIFT
        elif token == "NOT":
            return Operation.NOT
        else:
            raise Exception("bad operation: %s" % token)


class TokenType(Enum):
    NUMBER = 1
    WIRE = 2
    OPERATION = 3


@dataclass
class Operand:
    operation: Operation = Operation.NONE
    number: int = 0
    wire: str = ""


@dataclass
class Token:
    type: TokenType
    operand: Operand


def tokenize(string: str) -> List[Token]:
    tokens = []
    stop = False
    for token in string.split(' '):
        char = token[0]
        if char.isdigit():
            tokens.append(Token(TokenType.NUMBER,
                                Operand(number=int(token))))
        elif char.islower():
            tokens.append(Token(TokenType.WIRE,
                                Operand(wire=token)))
        elif char.isupper():
            tokens.append(Token(TokenType.OPERATION,
                                Operand(operation=Operation.from_string(token))))
    return tokens


@dataclass
class Wire:
    value: int = -1
    tokens: List[Token] = field(default_factory=lambda: [])


Wires = Dict[str, Wire]


def token_value(token: Token, wires: Wires) -> int:
    v: int = 0
    if token.type == TokenType.NUMBER:
        v = token.operand.number
    elif token.type == TokenType.WIRE:
        v = wire_eval(token.operand.wire, wires)
    else:
        assert False
    return v


def wire_eval(wire: str, wires: Wires) -> int:
    if wires[wire].value != -1:
        return wires[wire].value

    tokens: List[Token] = wires[wire].tokens

    # SIGNAL or WIRE
    if len(tokens) == 1:
        wires[wire].value = token_value(tokens[0], wires)
        return wires[wire].value

    # NOT
    if len(tokens) == 2 and tokens[0].type == TokenType.OPERATION:
        wires[wire].value = ~wire_eval(tokens[1].operand.wire, wires)
        return wires[wire].value

    # other operations
    if len(tokens) == 3 and tokens[1].type == TokenType.OPERATION:
        v1: int = token_value(tokens[0], wires)
        v2: int = token_value(tokens[2], wires)
        op: Operation = tokens[1].operand.operation

        v: int = 0
        if op == Operation.AND:
            v = v1 & v2
        elif op == Operation.OR:
            v = v1 | v2
        elif op == Operation.LSHIFT:
            v = v1 << v2
        elif op == Operation.RSHIFT:
            v = v1 >> v2
        else:
            assert False

        wires[wire].value = v
        return v
    return 0
