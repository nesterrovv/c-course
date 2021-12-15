// Вам доступны эти функции из прошлых заданий
size_t read_size();
void array_int_fill(int64_t* array, size_t size);
int64_t* array_int_read(size_t* size);

int64_t** marray_read( size_t* rows, size_t** sizes ) {
    *rows = read_size(); // read size using value by pointer
    *sizes = malloc(sizeof(size_t) * (*rows)); // malloc memory for sizes
    int64_t** my_array = malloc(sizeof(int64_t*) * (*rows)); // malloc memory for future
    for (size_t i = 0; i < *rows; ++i) {
        *(my_array + i) = array_int_read(*sizes+i); // fill array cell using read method
    }
    return my_array;
}

void marray_print(int64_t** marray, size_t* sizes, size_t rows) {
    for( size_t i = 0; i < rows; i = i + 1 ) {
        array_int_print( marray[i], sizes[i] );
        print_newline();
    }
}