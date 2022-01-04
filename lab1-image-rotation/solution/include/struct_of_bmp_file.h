//
// Created by Ivan Nesterov on 12/23/2021.
// Pasted structure from first chapter of lab description
#ifndef LAB1_IMAGE_ROTATION_STRUCT_OF_BMP_FILE_H
#define LAB1_IMAGE_ROTATION_STRUCT_OF_BMP_FILE_H
#include <stdint.h>


struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

#endif //LAB1_IMAGE_ROTATION_STRUCT_OF_BMP_FILE_H
