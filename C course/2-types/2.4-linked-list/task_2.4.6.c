void list_add_back( struct list** old, int64_t value ) {
    struct list* new_node = node_create(value);
    struct list* old_node = list_last(*old);
    if (old_node) // if current node exists (maybe no!)
        old_node -> next = new_node; // change link
    else
        *old = new_node; // else just replace NULL value to our node-parameter
}