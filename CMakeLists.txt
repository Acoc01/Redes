cmake_minimum_required(VERSION 3.10)
project(lab1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(server main.c tcp.c)
