//
// Created by Ivan Nesterov on 12/24/2021.
//

#ifndef LAB1_IMAGE_ROTATION_FILE_FOR_INPUT_AND_OUTPUT_H
#define LAB1_IMAGE_ROTATION_FILE_FOR_INPUT_AND_OUTPUT_H
#include <stdio.h> // for working with files

enum result_of_opening {
    OPENING_FOR_READ_ERROR = 31,
    OPENING_FOR_WRITING_ERROR = 32,
    SUCCESSFULLY_OPENED = 0
};

enum result_of_closing {
    CLOSED_SUCCESSFULLY = 0,
};

enum result_of_opening read_file(FILE** readable_file, const char* path_to_file);

enum result_of_opening write_file(FILE** writeable_file, const char* path_to_file);

enum result_of_opening print_result_of_opening(enum result_of_opening result);

enum result_of_closing close_file(FILE* file);

#endif //LAB1_IMAGE_ROTATION_FILE_FOR_INPUT_AND_OUTPUT_H
