cmake_minimum_required(VERSION 3.23)
project(clox C)

set(CMAKE_C_STANDARD 99)

add_executable(clox main.c common.h chunk.h chunk.c memory.h memmory.c debug.c debug.h value.h value.c vm.c vm.h compile.c compile.h scanner.c scanner.h)
