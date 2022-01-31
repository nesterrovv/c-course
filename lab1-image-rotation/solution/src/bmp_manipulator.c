//
// Created by Ivan Nesterov on 12/23/2021.
//

#include "bmp_manipulator.h"
#include "struct_of_bmp_file.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function for freeing memory from image
 * @param image
 */
void free_image(struct image* image) {
    free(image -> data);
}

/**
 * Function for receiving number of padding bytes
 * If the width is not a multiple of four, then it is padded with
 * garbage bytes to the nearest multiple of four. These bytes are called padding.
 * @param image is file, in witch number of paddings will be counted
 * @return number of paddings
 */
uint64_t get_number_of_padding(struct image const* image) {
    return (image -> width % 4);
}

/**
 * Function for creating new header
 * @param image is structure with image which will be used for header creating
 * @return created header
 */
struct bmp_header create_header(struct image const* image) {
    struct bmp_header new_header = {
            .bfType = 0x4D42, // hex description of bmp file from wikipedia
            // weight * height * size of 1 pixel + height * amount of padding-bytes + signature
            .bfileSize = (image -> width) * (image -> height) * sizeof(struct pixel) + (image -> height) *
                    get_number_of_padding(image) + sizeof(struct bmp_header),
            .bfReserved = 0,
            .bOffBits = sizeof(struct bmp_header), // size of signature
            .biSize = 40,
            .biWidth = image -> width,
            .biHeight = image -> height,
            .biPlanes = 1,
            .biBitCount = 24, // only 24-bit bmp files in solution
            .biCompression = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0};
    // size of (all file size - size of signature)
    new_header.biSizeImage = new_header.bfileSize - new_header.bOffBits; // size of "clear image"
    return new_header;
}

/**
 * Function for checking header of bmp file. It can be BMP (0x4D42), 24-bit type, with size 40,
 * without compression
 * @param header is checked header
 * @return result of checking
 */
enum result_of_reading check_header(const struct bmp_header header) {
    if (header.bfType != 0x4D42) {
        return INCORRECT_SIGNATURE_ERROR;
    }
    if (header.biBitCount != 24) {
        return INCORRECT_BITS_ERROR;
    }
    if (header.biSize != 40 || header.biCompression != 0 || (header.bfileSize != header.bOffBits + header.biSizeImage)) {
        return INCORRECT_HEADER_ERROR;
    }
    return SUCCESSFULLY_READ;
}

/**
 * Function for giving text representation for any result of file reading
 */
static char* const get_text_result_of_reading[] = {
        [SUCCESSFULLY_READ] = "Image has been loaded successfully.\n",
        [INCORRECT_SIGNATURE_ERROR] = "Incorrect signature (not .bmp). This type of file is not supported.\n",
        [INCORRECT_BITS_ERROR] = "Incorrect size. Only 24-bit files are supported.\n",
        [INCORRECT_HEADER_ERROR] = "Incorrect header of file.\n",
        [INCORRECT_PATH_TO_FILE_ERROR] = "File not found. Check path to it.\n"
};

/**
 * Function for giving text representation for any result of file writing
 */
static char* const get_text_result_of_writing[] = {
        [IMAGE_WRITING_ERROR] = "File writing error.\n",
        [SUCCESSFULLY_WRITTEN] = "Image is saved successfully.\n"
};

/**
 * Function for reading bmp file
 * @param file is readable file
 * @param image is readable image
 * @return reading result
 */
enum result_of_reading read_data_from_bmp(FILE* file, struct image* image){
    if (file == NULL)  return INCORRECT_PATH_TO_FILE_ERROR;
    struct bmp_header header;
    // read to header 1 item from file (is header of file)
    fread(&header, 1, sizeof(struct bmp_header), file);
    const enum result_of_reading header_reading_result = check_header(header);
    if (header_reading_result) return header_reading_result;
    // memory allocation for
    uint64_t data_size = header.biHeight * header.biWidth * sizeof(struct pixel); // necessary size definition
    image -> data = (struct pixel*) malloc(data_size); // memory for data
    image -> height = header.biHeight; // get height for image
    image -> width = header.biWidth; // get weight for image
    uint64_t paddings_amount = get_number_of_padding(image); // paddings-byte number definition
    for (size_t i = 0; i < header.biHeight; i++) { // data reading row by row
        // loop for moving into "row" of image and reading it
        fread(&(image -> data[i * image -> width]), sizeof(struct pixel), image -> width, file);
        // if it necessary, "row" will be supplemented by paddings-bytes, staring with current position, finishing in end of fow
        fseek(file, paddings_amount, SEEK_CUR); // SEEK_CUR param is current position
    } return SUCCESSFULLY_READ;
}

/**
 * Function for printing text of result of reading in standard output
 * @param result is printable result of reading
 */
enum result_of_reading print_reading_result(enum result_of_reading result) {
    printf("%s", get_text_result_of_reading[result]);
    return result;
}

/**
 * Function for writing data to bmp file
 * @param file is file which will be store written data
 * @param image is image which will be saved in file
 * @return writing result
 */
enum result_of_writing write_data_to_bmp(FILE* file, struct image const* image) {
    struct bmp_header header = create_header(image);
    uint64_t paddings_amount = get_number_of_padding(image);
    if (!fwrite(&header, 1, sizeof(struct bmp_header), file)) {
        return IMAGE_WRITING_ERROR; // if writing is impossible (permission denied etc.)
    }
    const struct pixel nulls[] = {{0},{0},{0}};
    for (size_t i = 0; i < image -> height; i++) {
        // if writing to any string is impossible
        if (!fwrite(&(image -> data)[i * image -> width], sizeof(struct pixel), image -> width, file)
                || (paddings_amount && !fwrite(nulls, 1, paddings_amount, file))) {
            return IMAGE_WRITING_ERROR;
        }
    } return SUCCESSFULLY_WRITTEN;
}

/**
 * Function for printing text of result of writing in standard output
 * @param result is printable result of writing
 */
enum result_of_writing print_writing_result(enum result_of_writing result){
    printf("%s", get_text_result_of_writing[result]);
    return result;
}

