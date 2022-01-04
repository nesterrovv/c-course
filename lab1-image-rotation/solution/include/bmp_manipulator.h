//
// Created by Ivan Nesterov on 12/23/2021.
//

#ifndef LAB1_IMAGE_ROTATION_BMP_MANIPULATOR_H
#define LAB1_IMAGE_ROTATION_BMP_MANIPULATOR_H
#include "stdio.h" // for working with files
#include "struct_of_bmp_file.h"

enum result_of_reading {
    SUCCESSFULLY_READ = 0,
    INCORRECT_SIGNATURE_ERROR = 11,
    INCORRECT_PATH_TO_FILE_ERROR = 12,
    INCORRECT_BITS_ERROR = 13,
    INCORRECT_HEADER_ERROR = 14
};

enum result_of_writing {
    SUCCESSFULLY_WRITTEN = 0,
    IMAGE_WRITING_ERROR = 21
};

enum result_of_reading read_data_from_bmp(FILE* file, struct image* image); // function for reading bmp file

enum result_of_reading print_reading_result(enum result_of_reading result); // return reading result

enum result_of_writing write_data_to_bmp(FILE* file, struct image const* image); // function for writing "image" to bmp file

enum result_of_writing print_writing_result(enum result_of_writing result); // return writing result

#endif //LAB1_IMAGE_ROTATION_BMP_FOR_INPUT_AND_OUTPUT_H
