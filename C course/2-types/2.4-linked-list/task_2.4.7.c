int64_t list_sum(const struct list* list) {
    int64_t sum = 0;
    while (list) {
        int64_t current_value = (int64_t) list -> value;
        sum += current_value;
        const struct list* next_node = (const struct list*) list -> next;
        list = next_node;
    }
    return sum;
}