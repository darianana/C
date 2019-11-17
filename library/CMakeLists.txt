cmake_minimum_required(VERSION 3.14)
project(library)

set(CMAKE_CXX_STANDARD 17)

add_executable(library main.cpp Matrix.cpp Vector.h Vector.cpp Base.h Matrix.h catch.hpp)

