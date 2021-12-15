// Вам доступны следующие функции:
size_t read_size();
int64_t* array_int_min( int64_t* array, size_t size );
int64_t** marray_read( size_t* rows, size_t* sizes[] );
void marray_free( int64_t** marray, size_t rows );
void marray_print(int64_t** marray, size_t* sizes, size_t rows);


// Указатель на минимальное из двух чисел.
// если хотя бы одно число NULL, то возвращать второе
// если оба числа NULL результат NULL
int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
    if (y == NULL) { // if one of nums is null - return other
        return x;    
    } else if (x == NULL) {
        return y;    
    } else {
        if (*x < *y) {
            return x;    
        } else {
            return y; 
        }
    }
}

// Вернуть адрес минимального элемента массива массивов
int64_t* marray_int_min( int64_t** marray, size_t* sizes, size_t rows ) {
  int64_t* minimal_array = NULL; // in start is null (for incorrect arrays there are no minimum)
    for (size_t i = 0; i < rows; i++) { // loop like in previous task
        int64_t* minimal_row = array_int_min(marray[i], sizes[i]); // find minimal row
        minimal_array = int64_ptr_min(minimal_array, minimal_row); // return adress of minimal from parametres
    }
    return minimal_array;
}

// Вычесть m изо всех элементов массива
void marray_normalize( int64_t** marray, size_t sizes[], size_t rows, int64_t m ) {
    for (size_t current_row = 0; current_row < rows; current_row++) { // loop for checking "two-dimensional" array, like matrix in math
        for (size_t current_column = 0; current_column < sizes[current_row]; current_column++) {
             marray[current_row][current_column] -= m;
        }
    }
}

// Прочитать, найти минимум и нормализовать массив, вывести результат
void perform() {
    size_t rows; // "variables" for int64_t** marray_read( size_t* rows, size_t* sizes[]);
    size_t* sizes;
    int64_t** marray = marray_read(&rows, &sizes);
    int64_t* min = marray_int_min(marray, sizes, rows);
    if (min != NULL) marray_normalize(marray, sizes, rows, *min); // if there are no minimum
    marray_print(marray, sizes, rows); // else, array is normalized and we can print it immideately
    marray_free(marray, rows); // clean memory like in previous tasks
    free(sizes);
}