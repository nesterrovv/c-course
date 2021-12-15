// return value witch shows "size" - is size_t type
size_t list_length(const struct list* list) {
    size_t length = 0;
    while(list) {
        struct list* new_pointer = list -> next; // "move" pointer "to the right"
        list = new_pointer;
        length++;
    }
    return length;
}
