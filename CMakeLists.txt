cmake_minimum_required(VERSION 3.29)
project(1 C)

set(CMAKE_C_STANDARD 23)

add_executable(1 main.c
        functions.c
        functions.h
        structures.h)
