struct list* list_read() {
    struct maybe_int64 input = maybe_read_int64();
    struct list* list = NULL;
    struct list* current_node = NULL;
    while (input.valid) {
        struct list* node = node_create(input.value);
        if (list == NULL) {
            list = node;
            current_node = list;
        } else {
            //struct list* new_link = list -> next;
            //node = new_link;
            list -> next = node;
            list = node;
        }
        input = maybe_read_int64();
       
    }
    return current_node;
}