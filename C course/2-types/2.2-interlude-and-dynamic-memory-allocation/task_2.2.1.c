// вы можете реализовать эти функции для более удобного считывания чисел
int64_t read_int64() {
    int64_t num;
    scanf("%" SCNd64, &num);
    return num;
}

size_t read_size() {
    size_t size;
    scanf("%zu", &size);
    return size;
}

// заполнить уже выделенный массив array размера size числами
void array_int_fill(int64_t *array, size_t size) {
    for (size_t index = 0; index < size; index++) {
        array[index] = read_int64();
    }
}

// Считать размер массива в *size, выделить память под массив и заполнить его числами.
int64_t *array_int_read(size_t *size) {
    *size = read_size();
    if (*size) {
        int64_t *array = malloc(*size * sizeof(uint64_t));
        array_int_fill(array, *size);
        return array;
    }
    return NULL; // if previous return is not successful
}