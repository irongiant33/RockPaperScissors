#resource for creating this file: https://cmake.org/cmake/help/latest/guide/tutorial/index.html#a-basic-starting-point-step-1

cmake_minimum_required(VERSION 3.10)

# set the project name
project(RockPaperScissors)

# add the executable
add_executable(RockPaperScissors src/play.c)