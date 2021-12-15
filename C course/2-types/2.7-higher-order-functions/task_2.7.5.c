/*
struct list {
    int64_t value;
    struct list* next;
};
*/
void print_int64(int64_t i);

struct list* node_create( int64_t value );
void list_destroy( struct list* list );

// function from previous task
struct list* add_new_node(struct list* node, int64_t value) {
    struct list* new_node = node_create(value);
    if (node != NULL) {
        node -> next = new_node;
    }
    return new_node;
}

/*  Сгенерировать список длины sz с помощью значения init и функции f
 Результат: init, f(init), f(f(init)), ... */
struct list* list_iterate( int64_t init_value, size_t size, int64_t (function) (int64_t)) {
    int64_t value = init_value;
    struct list* first_node = NULL;
    struct list* last_node = NULL;
    for (size_t index = 0; index < size; index++) {
        last_node = add_new_node(last_node, value);
        value = function(value);
        if (first_node == NULL) first_node = last_node;
    }
    return first_node;
}