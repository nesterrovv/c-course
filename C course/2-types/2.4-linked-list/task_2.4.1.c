struct list {
  int64_t value;
  struct list* next;
};

struct list* node_create(int64_t value) {
    struct list *list;
    list = (struct list*) malloc(sizeof(struct list));
    list -> value = value;
    list -> next = NULL;
    return(list);
}