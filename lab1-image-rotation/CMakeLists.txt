cmake_minimum_required(VERSION 3.21)
project(lab1_image_rotation C)

set(CMAKE_C_STANDARD 99)

add_executable(lab1_image_rotation
        src/main.c
        src/struct_of_bmp_file.h
        src/bmp_for_input_and_output.h
        src/bmp_for_input_and_output.c
        src/file_for_input_and_output.h
        src/file_for_input_and_output.c
        src/rotation_of_image.c
        src/rotation_of_image.h)
