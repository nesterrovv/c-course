//
// Created by Ivan Nesterov on 1/5/2022.
//

#include <stdio.h>
#include "../include/test_system.h"
#include "../include/memory_manipulator.h"
#include "../include/memory_debuger.h"

/**
 * Function for starting testing of my memory allocator.
 * It prints steps of testing to standard output
 */
void start_test_system() {
    printf("%s\n", "----- Heap initialization -----");
    void* heap = heap_init(10000);
    debug_heap(stdout, heap);
    printf("\n\n");

    printf("%s\n", "----- Normal successful memory allocation -----");
    void* first_block = _malloc(100);
    void* second_block = _malloc(400);
    _malloc(100);
    void* third_block = _malloc(1);
    _malloc(1000);
    debug_heap(stdout, heap);
    printf("\n\n");

    printf("%s\n", "----- Freeing one block from several allocated -----");
    _free(third_block);
    debug_heap(stdout, heap);
    printf("\n\n");

    printf("%s\n", "----- Freeing two blocks from several allocated ----- ");
    _free(second_block);
    _free(first_block);
    debug_heap(stdout, heap);
    printf("\n\n");

    printf("%s\n", "----- The memory is over, the new region of memory expands the old -----");
    _malloc(200);
    _malloc(10000);
    _malloc(10300);
    _malloc(666);
    debug_heap(stdout, heap);
    printf("\n\n");

    printf("%s\n", "Testing is over.");
}



