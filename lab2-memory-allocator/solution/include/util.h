//
// Created by Ivan Nesterov on 1/3/2022.
//

#ifndef LAB2_MEMORY_ALLOCATOR_UTIL_H
#define LAB2_MEMORY_ALLOCATOR_UTIL_H

#include <stddef.h>

inline size_t size_max(size_t x, size_t y) {
    return (x >= y) ? x : y;
}

_Noreturn void err(const char* message, ...);

#endif //LAB2_MEMORY_ALLOCATOR_UTIL_H
