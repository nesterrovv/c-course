cmake_minimum_required(VERSION 3.21)
project(lab2_memory_allocator C)

set(CMAKE_C_STANDARD 99)

add_executable(lab2_memory_allocator
        solution/src/main.c
        solution/include/memory_manipulator.h
        solution/src/memory_manipulator.c
        solution/include/memory_internals.h
        solution/include/util.h
        solution/include/memory_debuger.h
        solution/src/memory_debuger.c
        solution/src/util.c
        solution/src/test_system.c
        solution/include/test_system.h)
