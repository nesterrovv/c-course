//
// Created by Ivan Nesterov on 1/3/2022.
//

#include <stdio.h>
#include <stdarg.h>
#include "../include/memory_internals.h"
#include "../include/memory_manipulator.h"

void debug_struct_info(FILE* file, void const* address) {
    struct block_header const* header =  address;
    fprintf(file,"%10p %10zu %8s   ", address, header-> capacity.bytes, header-> is_free? "free" : "taken");
    for (size_t index = 0; index < DEBUG_FIRST_BYTES && index < header -> capacity.bytes; index++) {
        fprintf( file, "%hhX", header-> contents[index] );
    }
    fprintf(file, "\n" );
}

void debug_heap(FILE* file, void const* pointer) {
    fprintf( file, " ----- Heap view -----\n");
    fprintf( file, "%10s %10s %8s %10s\n", "start", "capacity", "status", "contents" );
    for(struct block_header const* header =  pointer; header; header = header -> next) {
        debug_struct_info( file, header );
    }
}

void debug_block(struct block_header* b, const char* fmt, ...) {

#ifdef DEBUG

    va_list args;
    va_start (args, fmt);
    vfprintf(stderr, fmt, args);
    memalloc_debug_struct_info(stderr, b);
    va_end(args);

#else
    (void) b; (void) fmt;
#endif
}

void debug(const char* fmt, ...) {
#ifdef DEBUG

    va_list args;
    va_start (args, fmt);
    vfprintf(stderr, fmt, args);
    va_end (args);

#else
    (void) fmt;
#endif

}
