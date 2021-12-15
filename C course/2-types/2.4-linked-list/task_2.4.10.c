struct maybe_int64 maybe_read_int64() {
    int64_t number;
    int user_input = scanf("%" SCNd64, &number);
    if (user_input == EOF) return none_int64;
    return some_int64(number);
}