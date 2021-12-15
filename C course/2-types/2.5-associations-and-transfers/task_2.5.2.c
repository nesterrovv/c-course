// I translated comments so that it doesn't look weird compared to everything else in English :)

struct heap_string {
  char* addr;
};

// copy to heap
struct heap_string halloc(const char* s) {
    // find length of string
    size_t length_of_string = 0;
    const char* s_copy = s;
    while(*s_copy != 0) {
        length_of_string++;
        s_copy++;
    }
    // copy length to new char* with equal length, which was found earlier
    char* string_copy = malloc(sizeof(char)*(length_of_string + 1));
    for (size_t index = 0; index <= length_of_string; index++) {
        string_copy[index] = s[index];
    }
    struct heap_string result = {.addr = string_copy};
    return result;
}

// free memory
void heap_string_free(struct heap_string h) {
    free(h.addr);
}