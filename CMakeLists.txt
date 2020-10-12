cmake_minimum_required(VERSION 3.17)
project(Algo2_TP1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Q1/division.cpp
        Q1/division.hpp
        Q1/polynome.cpp
        Q1/polynome.hpp
        Q1/rationnel.cpp
        Q1/rationnel.hpp
        Q4/grandentier.hpp
        Q4/grandentier.cpp
        Q4/multiplication.cpp
        Q4/tests.cpp)

add_executable(Algo2_TP1 ${SOURCE_FILES} Q1/main.cpp)