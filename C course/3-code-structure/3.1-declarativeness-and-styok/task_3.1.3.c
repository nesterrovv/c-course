/* Вам доступны:


struct maybe_int64 {
    int64_t value; 
    bool valid; 
};

struct maybe_int64 some_int64(int64_t i);

extern const struct maybe_int64 none_int64;

void maybe_int64_print( struct maybe_int64 i );
struct maybe_int64 maybe_read_int64();
void print_int64(int64_t i)
*/

void interpret_push(struct vm_state* state) {
  stack_push(& state->data_stack, state->ip->as_arg64.arg);
}

void interpret_iread(struct vm_state* state) {
    struct maybe_int64 number = maybe_read_int64();
    if (!number.valid) err("EOF");
    stack_push(& state -> data_stack, number.value);
}
void interpret_iadd(struct vm_state* state) {
    struct maybe_int64 first_number = stack_pop(&state -> data_stack);
    struct maybe_int64 second_number = stack_pop(&state -> data_stack);
    if (!first_number.valid || !second_number.valid) err("Expected 2 arguments for the \"add\" command");
    stack_push(& state -> data_stack, first_number.value + second_number.value);
}
void interpret_iprint(struct vm_state* state ) {
    struct maybe_int64 n = stack_pop(&state->data_stack);
    if (!n.valid) err("Nothing to print");
    print_int64(n.value);
}

/* Подсказка: можно выполнять программу пока ip != NULL,
    тогда чтобы её остановить достаточно обнулить ip */
void interpret_stop(struct vm_state* state ) {
    state -> ip = 0;
}

typedef void (*interpreter)(struct vm_state*);

const interpreter interpreters[] = {
    [BC_PUSH] = interpret_push,
    [BC_IREAD] = interpret_iread,
    [BC_IADD] = interpret_iadd,
    [BC_IPRINT] = interpret_iprint,
    [BC_STOP] = interpret_stop
};

void interpret(struct vm_state* state) {
    union ins* first_ip = state -> ip;
    while(true) {
        enum opcode current_instruction = state -> ip -> opcode;
        (interpreters[current_instruction]) (state);
        if (state -> ip == NULL) break;
        (state -> ip)++;
    }
}