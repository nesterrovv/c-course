#include "../include/struct_of_bmp_file.h"
#include "../include/bmp_manipulator.h"
#include "../include/file_manipulator.h"
#include "../include/rotation_of_image.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function for freeing memory from image
 * @param image
 */
void free_image(struct image* image) {
    free(image -> data);
}

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;
    if (argc != 3) {
        printf("Incorrect number of arguments. 3 is necessary. (1st is used for starting a program)");
        printf("You need write input.bmp and output.bmp, separated by 1 space");
        return 1;
    }
    const char *path_to_old_file = argv[1];
    const char *path_to_new_file = argv[2];
    printf("Input file with initial image is: '%s' \n", path_to_old_file);
    printf("Output file with saved image is: '%s' \n", path_to_new_file);
    struct image image = {0};
    FILE * old_file = NULL;
    enum result_of_opening status_of_opening = read_file(&old_file, path_to_old_file);
    if(print_result_of_opening(status_of_opening)){
        return status_of_opening;
    }
    enum result_of_reading result_of_reading = read_data_from_bmp(old_file, &image);
    close_file(old_file);
    if(print_reading_result(result_of_reading)){
        return result_of_reading;
    }
    // rotate three times clockwise because I haven't figured out how to rotate once after :(
    struct image rotated_image1 = rotate_image(image);
    struct image rotated_image2 = rotate_image(rotated_image1);
    struct image rotated_image3 = rotate_image(rotated_image2);
    FILE *new_file = NULL;
    enum result_of_opening result_of_writing = write_file(&new_file, path_to_new_file);
    if(print_result_of_opening(result_of_writing)){
        return result_of_writing;
    }
    uint8_t status_of_writing = write_data_to_bmp(new_file,&rotated_image3);
    close_file(new_file);
    if(print_writing_result(status_of_writing)){
        return status_of_writing;
    }
    // free all 4 images from memory (old and 2 incorrectly rotated image & final image too)...
    free_image(&image);
    free_image(&rotated_image1);
    free_image(&rotated_image2);
    free_image(&rotated_image3);
    printf("Memory was freed successfully.\n");
    return 0;
}
