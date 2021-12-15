struct maybe_int64 list_at(const struct list* list, size_t index) {
    // const struct maybe_int64 none_int64 = { 0 };
    if (index < 0) {
        return none_int64;
    }
    for (size_t list_index = 0; list_index < index; list_index++) {
        if (list == NULL) {
             return none_int64; // if list is empty
        }
        const struct list* next_element = list -> next;
        list = next_element;
    }
    if (list == NULL) {
        return none_int64; // if element with index = paremeter index is link to NULL;
    } else {
        return some_int64(list -> value);
    }
}