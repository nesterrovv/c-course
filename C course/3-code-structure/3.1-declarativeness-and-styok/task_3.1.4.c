/* Вам уже доступны функции: */
bool stack_push( struct stack* s, int64_t value );
struct maybe_int64 stack_pop( struct stack* s );

/*
  struct maybe_int64 {
  int64_t value;
  bool valid;
  };
*/
struct maybe_int64 some_int64(int64_t i);
/*  const struct maybe_int64 none_int64; */



/*  Интерпретаторы команд */
void interpret_swap (struct vm_state* state)  {
    struct maybe_int64 first_number = stack_pop(& state -> data_stack);
    struct maybe_int64 second_number = stack_pop(& state -> data_stack);
    if (!first_number.valid || !second_number.valid) err("Expected 2 parametres for \"swap\" command");
    stack_push(&state -> data_stack, first_number.value);
    stack_push(&state -> data_stack, second_number.value);
}

void interpret_pop (struct vm_state* state)  {
    stack_pop(& state -> data_stack);
}

void interpret_dup (struct vm_state* state)  {
    struct maybe_int64 number = stack_pop(& state -> data_stack);
    if (!number.valid) err("Expected 1 parameter for \"dup\" command");
    stack_push(&state->data_stack, number.value);
    stack_push(&state->data_stack, number.value);
}

// Эти функции поднимают операции над числами на уровень стековых операций
// lift_unop применяет операцию к вершине стека;
void lift_unop( struct stack* s, int64_t (f) (int64_t)) { 
    struct maybe_int64 parameter = stack_pop(s);
    if (!parameter.valid) err("Expected 1 parameter for \"lift_unop\" command");
    int64_t new_number = f(parameter.value);
    stack_push(s, new_number);
}

// lift_binop забирает из стека два аргумента,
// применяет к ним функцию от двух переменных и возвращает в стек результат
void lift_binop( struct stack* s, int64_t (f)(int64_t, int64_t)) {
    // using pop command logic, THIS ORDER is correct
    struct maybe_int64 second_number = stack_pop(s);
    struct maybe_int64 first_number = stack_pop(s);
    if (!first_number.valid || !second_number.valid) err("Expected 2 parameteres for \"lift_binop\" command");
    int64_t new_number = f(first_number.value, second_number.value);
    stack_push(s, new_number);
}


int64_t i64_add(int64_t a, int64_t b) { return a + b; }
int64_t i64_sub(int64_t a, int64_t b) { return a - b; }
int64_t i64_mul(int64_t a, int64_t b) { return a * b; }
int64_t i64_div(int64_t a, int64_t b) { return a / b; }
int64_t i64_cmp(int64_t a, int64_t b) { if (a > b) return 1; else if (a < b) return -1; return 0; }

int64_t i64_neg(int64_t a) { return -a; }

void interpret_iadd( struct vm_state* state ) { lift_binop(& state->data_stack, i64_add); }
void interpret_isub( struct vm_state* state ) { lift_binop(& state->data_stack, i64_sub); }
void interpret_imul( struct vm_state* state ) { lift_binop(& state->data_stack, i64_mul); }
void interpret_idiv( struct vm_state* state ) { lift_binop(& state->data_stack, i64_div); }
void interpret_icmp( struct vm_state* state ) { lift_binop(& state->data_stack, i64_cmp); }

void interpret_ineg( struct vm_state* state ) { lift_unop (& state->data_stack, i64_neg);  }