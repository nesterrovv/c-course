//
// Created by Ivan Nesterov on 12/24/2021.
//

#include "file_manipulator.h"
#include <stdio.h>

/**
 * Enum for giving text representation for opening the file
 */
char* const get_text_result_of_opening[] = {
        [OPENING_FOR_READ_ERROR] ="File opening error for reading.\n",
        [OPENING_FOR_WRITING_ERROR] ="File opening error for writing.\n",
        [SUCCESSFULLY_OPENED] ="File is opened successfully.\n",
};

/**
 * Function for checking the ability to open a file for reading
 * @param readable_file is verifiable file
 * @param path_to_file is path to verifiable file
 * @return result of file opening for reading
 */
enum result_of_opening read_file(FILE** readable_file, const char* path_to_file) {
    *readable_file = fopen(path_to_file, "rb"); // try read some file binary
    if (!*readable_file) { // are there file at the specified path?
        return OPENING_FOR_READ_ERROR;
    }
    return SUCCESSFULLY_OPENED;
}

/**
 * Function for checking the ability to open a file for writing
 * @param writeable_file is verifiable file
 * @param path_to_file is path to verifiable file
 * @return result of file opening for writing
 */
enum result_of_opening write_file(FILE** writeable_file, const char* path_to_file) {
    *writeable_file = fopen(path_to_file, "wb");
    if (!*writeable_file) {
        return OPENING_FOR_WRITING_ERROR;
    } else return SUCCESSFULLY_OPENED;
}

/**
 * Function for printing text status of working with file to standard output
 * @param printable_status is status which will be printed to standard output in text representation
 */
enum result_of_opening print_result_of_opening(enum result_of_opening printable_result) {
    printf("%s", get_text_result_of_opening[printable_result]);
    return printable_result;
}

/**
 * Function for closing file. Prints status to the standard output.
 * @param file which will be closed
 * @return closing status
 */
enum result_of_closing close_file(FILE* closeable_file) {
    fclose(closeable_file);
    printf("File is closed successfully.\n");
    return CLOSED_SUCCESSFULLY;
}
