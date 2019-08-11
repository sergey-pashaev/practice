cmake_minimum_required(VERSION 3.1)

testable(ex.1)
testable(ex.2)
testable(ex.3)
testable(ex.4)
testable(ex.5)
testable(ex.6)
testable(ex.7)
testable(ex.8)
testable(ex.9)

testable(ex.10)
target_link_libraries(dcp-ex.10 PRIVATE pthread) # TODO: add link targets as args to testable

testable(ex.11)
testable(ex.12)
