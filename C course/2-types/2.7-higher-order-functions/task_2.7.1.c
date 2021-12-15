/*
struct list {
    int64_t value;
    struct list* next;
};
*/

void print_int64(int64_t i);

void print_int64_with_space(int64_t number) {
    printf("%" PRId64" ", number);
}

/* Запустить функцию f на каждом элементе списка  */
void list_foreach(const struct list* l, void (f) (int64_t)) {
    while(l != NULL) {
        f(l->value);
        const struct list* new_l = l -> next;
        l = new_l;
    }
}

/* Вывести список с помощью foreach и дополнительной функции */
void list_print(const struct list* l) { 
    list_foreach(l, print_int64_with_space);
}