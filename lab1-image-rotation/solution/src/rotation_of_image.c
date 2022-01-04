//
// Created by Ivan Nesterov on 12/27/2021.
//

#include "../include/rotation_of_image.h"
#include <stdlib.h>

struct image rotate_image(struct image const rotatable_image) {
    struct image new_image = {.height = rotatable_image.width,
                              .width = rotatable_image.height};
    new_image.data = malloc(rotatable_image.height * rotatable_image.width * sizeof(struct pixel));
    for (uint64_t column = 0; column < rotatable_image.height; column++) {
        for (uint64_t row = 0; row < rotatable_image.width; row++) {
            new_image.data[column+((new_image.height-row-1) * new_image.width)] = rotatable_image.data[row+column * rotatable_image.width];
        }
    }
    return new_image;
}
