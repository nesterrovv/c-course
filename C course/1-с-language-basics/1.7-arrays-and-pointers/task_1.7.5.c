void array_fib(int* array, int* limit) {
    int size = limit - array;
    if (size > 2) {
        array[0] = 1; array[1] = 1;
        for (int i = 2; i < size; i++) {
            array[i] = array[i-1] + array[i-2];
        }
    }
    if (size == 2) {
        array[0] = 1; array[1] = 1;
    }
    if (size == 1) {
        array[0] = 1;
    }
}