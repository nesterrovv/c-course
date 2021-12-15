/*
struct list {
    int64_t value;
    struct list* next;
};
*/
/* Вы можете пользоваться следующими функциями */
void print_int64(int64_t i);
struct list* node_create( int64_t value );

struct list* add_new_node(struct list* node, int64_t value) {
    struct list* new_node = node_create(value);
    if (node != NULL) {
        node -> next = new_node;
    }
    return new_node;
}


/*  Создать новый список, в котором каждый элемент получен из соответствующего
    элемента списка l путём применения функции f */
struct list* list_map(const struct list* list, int64_t (function) (int64_t))  {
    struct list* new_list = NULL;
    struct list* current_position = NULL;
    while(list != NULL) {
        int64_t new_value = function(list -> value); // receive new value
        new_list = add_new_node(new_list, new_value); // save new value to current position in list
        if (current_position == NULL) { // if current position is not exist
            current_position = new_list;
        }
        list = list -> next;
    }
    return current_position;
}

int64_t get_int64_t(int64_t number) {
    return number;
}

int64_t get_abs_of_number(int64_t number) {
    if (number >= 0) return number;
    else return number * (-1);
}

struct list* list_copy(const struct list* list) {
    return list_map(list, &get_int64_t);
}

struct list* list_abs(const struct list* list) {
    return list_map(list, &get_abs_of_number);
}