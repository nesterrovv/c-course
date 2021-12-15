void array_reverse(int* array, int size) {
    for (int i = 0; i < size/2; i++) {
        int tmp = array[i];
        array[i] = array[size - 1 - i];
        array[size - 1 - i] = tmp;
    }
}

void array_reverse_ptr(int* array, int* limit) {
    int size = limit - array;
    for (int i = 0; i < size/2; i++) {
        int tmp = array[i];
        array[i] = array[size - 1 - i];
        array[size - 1 - i] = tmp;
   }
}