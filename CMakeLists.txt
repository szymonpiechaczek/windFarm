cmake_minimum_required(VERSION 3.9)
project(windFarm)

set(CMAKE_CXX_STANDARD 17)

add_executable(windFarm main.cpp DataParser.cpp DataParser.h)