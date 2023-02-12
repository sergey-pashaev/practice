import re

from typing import List
from enum import Enum
from dataclasses import dataclass


SIZE: int = 1000


@dataclass
class Point:
    i: int = 0
    j: int = 0


class Command(Enum):
    ON = 1
    OFF = 2
    TOGGLE = 3


@dataclass
class Instruction:
    command: Command
    src: Point
    dst: Point


INSTRUCTION_RX = re.compile(
    r"(turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+)"
)


def read_instruction(line: str) -> Instruction:
    match = INSTRUCTION_RX.match(line)
    assert match is not None

    src = Point(int(match.group(2)), int(match.group(3)))
    dst = Point(int(match.group(4)), int(match.group(5)))
    cmd = match.group(1)

    if cmd == "turn on":
        cmd = Command.ON
    elif cmd == "turn off":
        cmd = Command.OFF
    elif cmd == "toggle":
        cmd = Command.TOGGLE
    return Instruction(Command(cmd), src, dst)
