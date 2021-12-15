// Вам доступна функция
struct list* node_create( int64_t value );

void list_add_front(struct list** old, int64_t value ) {
    struct list* new_node = node_create(value);
    new_node -> next = *old;
    *old = new_node;    
}