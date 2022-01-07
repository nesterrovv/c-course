//
// Created by Ivan Nesterov on 1/3/2022.
//

#ifndef LAB2_MEMORY_ALLOCATOR_MEM_DEBUGER_H
#include "memory_internals.h"
#include <stdio.h>

void debug_struct_info(FILE* f, void const* address);

void debug_heap(FILE* f, void const* ptr);

void debug_block(struct block_header* b, const char* fmt, ...);

void debug(const char* fmt, ...);

#endif