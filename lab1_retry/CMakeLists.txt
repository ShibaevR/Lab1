cmake_minimum_required(VERSION 3.17)
project(lab1_retry C)

set(CMAKE_C_STANDARD 99)

add_executable(lab1_retry main.c matrix.c matrix.h element.c element.h tests.c tests.h fieldinfo.h fieldinfo.c)