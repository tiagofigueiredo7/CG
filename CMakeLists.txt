cmake_minimum_required(VERSION 3.10)
project(CG)

include_directories(include)

add_executable(generator src/generator/main.cpp src/generator/primitives.cpp src/utils/utils.cpp )