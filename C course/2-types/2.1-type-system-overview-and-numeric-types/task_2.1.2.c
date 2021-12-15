size_t count_zeroes(const void *data, size_t sz) {
    size_t counter = 0;
    for (size_t index = 0; index < sz; index++) {
        if (((uint8_t*) data)[index] == 0) {
            counter++;
        }
    }
    return counter;
}