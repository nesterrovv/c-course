//
// Created by Ivan Nesterov on 1/2/2022.
//

#include <stdarg.h>
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/memory_internals.h"
#include "../include/memory_manipulator.h"
#include "../include/util.h"

void debug_block(struct block_header* b, const char* fmt, ...);
void debug(const char* fmt, ...);

extern inline block_size size_from_capacity(block_capacity cap);
extern inline block_capacity capacity_from_size(block_size sz);

/**
 * Function for checking if block is big enough
 * (it's capacity greater than query)
 * @param query necessary amount of memory
 * @param block is considered block
 * @return status of checking
 */
static bool block_is_big_enough(size_t query, struct block_header* block) {
    return block -> capacity.bytes >= query;
}

/**
 * Function for counting amount of pages.
 * Page is block of memory with fixed size
 * @param memory is the amount of memory that should be allocated on the desired number of pages
 * @return amount of pages
 */
static size_t pages_count(size_t memory) {
    return memory / getpagesize() + ((memory % getpagesize()) > 0);
}

/**
 * Function for searching amount of bytes which is necessary for this memory amount,
 * because it's return (bytes in one page) * (amount of pages)
 * @param memory is the amount of memory for which the required number of bytes is sought
 * @return amount of bytes
 */
static size_t round_pages(size_t memory) {
    return getpagesize() * pages_count(memory);
}

/**
 * Function for initialization a new block of memory
 * @param address is address of current memory block
 * @param block_size is size of current memory block
 * @param next_address is address of next memory block
 */
static void block_init( void* restrict address, block_size block_size, void* restrict next_address) {
    *((struct block_header*) address) = (struct block_header) {
            .next = next_address,
            .capacity = capacity_from_size(block_size),
            .is_free = true
    };
}

/**
 * Function for allocating minimal necessary block of memory.
 * It returns round_pages value or region_min_size if it greater then necessary memory amount
 * @param query necessary memory amount
 * @return region with actual size
 */
static size_t region_actual_size(size_t query) {
    return size_max(round_pages(query ), REGION_MIN_SIZE);
}

extern inline bool region_is_invalid(const struct region* region);

static void* map_pages(void const* address, size_t length, int additional_flags) {
    return mmap((void*) address, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS |
    additional_flags , 0, 0 );
}

/* allocate region of memory and initialize it as a block */
/**
 * Function for allocating region of memory and it's initialization as a block
 * @param address is address of region of memory
 * @param necessary_query is necessary memory amount
 * @return created region of memory
 */
static struct region alloc_region(void const* address, size_t necessary_query) {
    /*  ??? */
    necessary_query = region_actual_size(necessary_query);
    void *next_address = map_pages(address, necessary_query, MAP_FIXED);
    struct region new_region;
    if(next_address == MAP_FAILED) {
        next_address = map_pages(address, necessary_query, 0);
        new_region = (struct region) {next_address, necessary_query, false};
    } else {
        new_region = (struct region) {next_address, necessary_query, true};
    }
    block_init(next_address, (block_size) {necessary_query}, NULL);
    return new_region;
}

static void* block_after(struct block_header const* block);

/**
 * Function for initialization heap of memory
 * @param initial_query is necessary amount of memory
 * @return address of heap
 */
void* heap_init(size_t initial_query) {
    const struct region region = alloc_region(HEAP_START, initial_query);
    if (region_is_invalid(&region)) {
        return NULL;
    } else {
        return region.address;
    }
}

#define BLOCK_MIN_CAPACITY 24

/*  --- block split (if found block is too big)--- */

/**
 * Function for checking if block is splittable
 * @param block is considered block of memory
 * @param query is necessary memory amount
 * @return status of checking
 */
static bool block_splittable(struct block_header* restrict block, size_t query) {
    return block -> is_free && query + offsetof(struct block_header, contents) +
            BLOCK_MIN_CAPACITY <= block -> capacity.bytes;
}

/**
 * Function for splitting block if it too big
 * @param block is considered block
 * @param query is necessary memory amount
 * @return status of checking
 */
static bool split_if_too_big(struct block_header* block, size_t query) {
    /*  ??? */
    // if this block is splittable (maybe is not too big :) )
    if (block_splittable(block, query)) {
        // init new part of big block, and add query parameter to it content
        struct block_header* second_block = (struct block_header*) (block -> contents + query);
        // define necessary size for this block
        block_size size_of_second_block = (block_size) {block -> capacity.bytes - query};
        // after that, initialize block "normally"
        block_init(second_block, size_of_second_block, block->next);
        // define new parameters of "old" part of block
        block -> capacity.bytes = query;
        block -> next = second_block;
        return true;
    }
    return false;
}


/*  --- merging adjacent free blocks --- */

/**
 * Function for founded next block of memory
 * @param block is current block of memory
 * @return status of checking
 */
static void* block_after(struct block_header const* block) {
    return (void*) (block -> contents + block -> capacity.bytes);
}

/**
 * Function for checking, that two blocks are next to each other
 * @param first is first block for checking
 * @param second is second block for checking
 * @return result of checking
 */
static bool blocks_continuous(struct block_header const* first, struct block_header const* second) {
    return (void*) second == block_after(first);
}

/**
 * Function for checking the possibility of merging two blocks into one
 * @param first is first block, which are checking for merging
 * @param second is second block, which are checking for merging
 * @return result of checking
 */
static bool mergeable(struct block_header const* restrict first, struct block_header const* restrict second) {
    return first -> is_free && second -> is_free && blocks_continuous(first, second);
}

/**
 * Function for merging some memory block with the next
 * @param block is block that will merge with the next
 * @return result of merging
 */
static bool try_merge_with_next(struct block_header* block) {
    /*  ??? */
    // define link to new block
    struct block_header* next_block = block -> next;
    // if new block is defined % blocks are mergeable, then we can "create" merged block
    if (next_block != NULL && mergeable(block, next_block)) {
        // redefine characteristics and link to next block (is link to next from last block)
        block -> capacity.bytes = block -> capacity.bytes + next_block -> capacity.bytes + offsetof(struct block_header, contents);
        block -> next = next_block -> next;
        return true;
    } else return false;
}


/*  --- ... if heap size is enough for... --- */

struct block_search_result {
    enum {BSR_FOUND_GOOD_BLOCK, BSR_REACHED_END_NOT_FOUND, BSR_CORRUPTED} type;
    struct block_header* block;
};

/**
 * A function for combining a sequence of blocks into one large one.
 * Two blocks are merged, the link to the next element is redefined
 * and the algorithm is repeated
 * @param block is block, starting from which the attempt to combine all subsequent
 * @return result of combining
 */
static bool try_merge_with_next_to_end( struct block_header* block ) {
    bool checker = false;
    // while next block is defined
    while(block -> next) {
        // combine blocks in loop and break when it's will become impossible
        if (try_merge_with_next(block)) {
            checker = true;
        } else break;
    }
    return checker;
}

/**
 * Function for searching good block with necessary size.
 * Or it returns last "good" block for it
 * @param block is current block
 * @param size is necessary size of "new" block
 * @return result of block searching
 */
static struct block_search_result find_good_or_last  (struct block_header* restrict block, size_t size)    {
    /* ??? */
    struct block_header* current_block = block;
    while (current_block -> next != NULL) {
        try_merge_with_next_to_end(current_block);
        if (block_is_big_enough(size, current_block) && (current_block -> is_free == true)) {
            return (struct block_search_result) {.block = current_block, .type = BSR_FOUND_GOOD_BLOCK};
        }
        struct block_header* new_block = current_block -> next;
        current_block = new_block;
    }
    return (struct block_search_result) {.block = current_block, .type = BSR_REACHED_END_NOT_FOUND};
}

/**
 * Function for finding necessary memory existing. It tries to allocate memory on the heap
 * starting at block 'block' without trying to expand the heap.
 * Can be reused as soon as the heap is expanded.
 * @param query is necessary memory amount
 * @param block is considered block of memory
 * @return result of searching
 */
static struct block_search_result try_memalloc_existing ( size_t query, struct block_header* block ) {
    struct block_search_result necessary_result = find_good_or_last(block, query);
    if (necessary_result.type == BSR_FOUND_GOOD_BLOCK) {
        split_if_too_big(necessary_result.block, query);
    }
    return necessary_result;
}


/**
 * Function for growing heap to necessary size
 * @param last is last block from considered heap
 * @param query is necessary size of heap
 * @return address of new region of memory
 */
static struct block_header* grow_heap( struct block_header* restrict last, size_t query ) {
    /*  ??? */
    query += offsetof (struct block_header, contents);
    void* address = last -> contents + last -> capacity.bytes;
    const struct region new_region = alloc_region(address, query);
    if (region_is_invalid(&new_region)) return NULL;
    last -> next = (struct block_header*) new_region.address;
    return new_region.address;
}

/*  Implements the capture of the malloc logic and returns the header of the allocated block */
/**
 * Function for implementing the capture of the malloc logic
 * @param query is necessary memory amount
 * @param heap_start address of first block of considered heap
 * @return header of the allocated block
 */
static struct block_header* memalloc(size_t query, struct block_header* heap_start) {
    /*  ??? */
    if (query < BLOCK_MIN_CAPACITY) {
        query = BLOCK_MIN_CAPACITY;
    }
    if (heap_start == NULL) {
        return NULL;
    }
    struct block_search_result result_block = try_memalloc_existing(query, heap_start);
    if (result_block.type == BSR_CORRUPTED) {
        return NULL;
    }
    if (result_block.type == BSR_REACHED_END_NOT_FOUND) {
        if (!grow_heap(result_block.block, query)) {
            return NULL;
        } else result_block = try_memalloc_existing(query, heap_start);
    }
    result_block.block -> is_free = false;
    return result_block.block;
}

/**
 * My realization of malloc function from standard library
 * @param query is necessary memory amount
 * @return address of allocated memory
 */
void* _malloc( size_t query ) {
    struct block_header* const address = memalloc( query, (struct block_header*) HEAP_START );
    if (address) return address -> contents;
    else return NULL;
}

/**
 * Function for returning header of considering block of memory
 * @param contents is considered content from memory
 * @return address to header
 */
static struct block_header* block_get_header(void* contents) {
    return (struct block_header*) (((uint8_t*)contents)-offsetof(struct block_header, contents));
}

/**
 * My realization of free function from standard library
 * @param mem is freeing memory
 */
void _free( void* mem ) {
    if (!mem) return ;
    struct block_header* header = block_get_header( mem );
    header->is_free = true;
    /*  ??? */
    try_merge_with_next_to_end(header);
}
