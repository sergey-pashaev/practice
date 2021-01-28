cmake_minimum_required(VERSION 3.1)

runnable(example)
target_link_libraries("${PROJECT_NAME}-example" PRIVATE benchmark pthread)
