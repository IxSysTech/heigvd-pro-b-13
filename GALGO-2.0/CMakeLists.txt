cmake_minimum_required(VERSION 3.13)
project(GALGO_2_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(GALGO_2_0
        src/Chromosome.hpp
        src/Converter.hpp
        src/Evolution.hpp
        src/example.cpp
        src/Galgo.hpp
        src/GeneticAlgorithm.hpp
        src/Parameter.hpp
        src/Population.hpp
        src/Randomize.hpp
        LICENSE.txt
        README.md)
