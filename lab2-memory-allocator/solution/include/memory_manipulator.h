//
// Created by Ivan Nesterov on 1/2/2022.
//

#ifndef LAB2_MEMORY_ALLOCATOR_MEMORY_MANIPULATOR_H
#define LAB2_MEMORY_ALLOCATOR_MEMORY_MANIPULATOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <sys/mman.h>

#define HEAP_START ((void*)0x04040000)

void* _malloc( size_t query );

void  _free( void* mem );

void* heap_init( size_t initial_size );

#define DEBUG_FIRST_BYTES 4

void debug_struct_info( FILE* f, void const* address );

void debug_heap( FILE* f,  void const* ptr );


#endif //LAB2_MEMORY_ALLOCATOR_MEMORY_MANIPULATOR_H
