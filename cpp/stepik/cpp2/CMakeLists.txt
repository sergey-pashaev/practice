cmake_minimum_required(VERSION 3.1)

project(stepik.cpp2)

runnable(ex.1.2.5)
runnable(ex.1.2.11)
runnable(ex.1.4.4)
runnable(ex.1.4.7)
runnable(ex.1.5.7)
runnable(ex.1.6.10)

runnable(ex.2.1.13)
runnable(ex.2.2.5)
runnable(ex.2.3.3)
runnable(ex.2.3.5)
runnable(ex.2.3.11)
runnable(ex.2.3.13)
runnable(ex.2.4.10)

runnable(ex.3.1.9)
runnable(ex.3.3.12)
runnable(ex.3.5.9)

runnable(ex.5.1.4)
target_link_libraries(stepik.cpp2-ex.5.1.4 PRIVATE pthread)
runnable(ex.5.1.6)
target_link_libraries(stepik.cpp2-ex.5.1.6 PRIVATE pthread)

runnable(ex.5.3.5)
runnable(ex.5.3.7)
runnable(ex.5.3.9)
runnable(ex.5.3.12)
