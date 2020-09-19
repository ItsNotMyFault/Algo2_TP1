cmake_minimum_required(VERSION 3.17)
project(Algo2_TP1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        division.cpp
        division.hpp
        main.cpp
        polynome.cpp
        polynome.hpp
        rationnel.cpp
        rationnel.hpp)

add_executable(Algo2_TP1 ${SOURCE_FILES} main.cpp)