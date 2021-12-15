// эти функции вы уже реализовали на предыдущих шагах
int64_t* array_int_read( size_t* size );
int64_t* array_int_min( int64_t* array, size_t size); 

// Выводит None если x == NULL, иначе число, на которое указывает x.
void intptr_print( int64_t* x ) {
    if (x == NULL) printf("None");
    else printf("%" PRId64, *x); // signed 64 int, value by pointer
}

void perform() {
    size_t size = 0;
    int64_t* array = array_int_read(&size); // receive array using adress of first item as a parameter
    if ((array == NULL) || (size == NULL) || (size <= 0)) { // if sth is wrong ???
        intptr_print(NULL); // print null because array is incorrect
    }
    int64_t* min = array_int_min(array, size); // if array is good - find it's minimym
    intptr_print(min); // use previous method - in this case array must be correct => minimum is exist
    free(array); // to clean memory, like finalize method in Java
}