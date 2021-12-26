/*

struct array_int {
  int64_t* data;
  size_t size;
};

struct stack {
  size_t count;
  struct array_int data;
};

*/

void interpret(struct vm_state* state, ins_interpreter * const  (actions)[]) {
    for (; state->ip ;) {
        const union ins* ins = state->ip;
        const struct ins_descr* ins_descr = instructions + ins->opcode;
        if (((int64_t) state -> data_stack.count +
        (int64_t) ins_descr -> stack_delta) > (int64_t) state -> data_stack.data.size) {
            printf("Stack overflow\n");
            break;
        }
        if (state -> data_stack.count < ins_descr -> stack_min) {
            printf("Stack underflow\n");
            break;
        }
        actions[ins->opcode](state);
        if (!ins_descr->affects_ip) { 
            state->ip = state->ip + 1;
        }
    }