//
// Created by Ivan Nesterov on 1/2/2022.
//

#ifndef LAB2_MEMORY_ALLOCATOR__MEMORY_INTERNALS_H
#define LAB2_MEMORY_ALLOCATOR__MEMORY_INTERNALS_H

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

#define REGION_MIN_SIZE (2 * 4096)

struct region {
    void* address;
    size_t size;
    bool extends;
};

static const struct region REGION_INVALID = {0};

inline bool region_is_invalid(const struct region* region) {
    return region -> address == NULL;
}

typedef struct {size_t bytes;} block_capacity;

typedef struct {size_t bytes;} block_size;

struct block_header {
    struct block_header* next;
    block_capacity capacity;
    bool is_free;
    uint8_t contents[];
};

inline block_size size_from_capacity(block_capacity capacity) {
    return (block_size) {capacity.bytes + offsetof(struct block_header, contents)};
}

inline block_capacity capacity_from_size(block_size size) {
    return (block_capacity) {size.bytes - offsetof(struct block_header, contents)};
}

#endif
