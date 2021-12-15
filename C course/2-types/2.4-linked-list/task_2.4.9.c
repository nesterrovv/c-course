void list_add_front( struct list** old, int64_t value );

// создать перевернутую копию списка
struct list* list_reverse(const struct list* list) {
    struct list* copy_of_list = NULL;
    while (list != NULL) {
        list_add_front(&copy_of_list, list -> value);
        const struct list* new_link = list -> next;
        list = new_link;
    }
    return copy_of_list;
}