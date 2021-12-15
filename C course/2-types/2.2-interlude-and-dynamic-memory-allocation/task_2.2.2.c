int64_t* array_int_min( int64_t* array, size_t size ) {
    if (size == 0) return NULL; // if array is empty - there are no minimum
    int64_t* minimum = array; // type of pointer to item is equal type from signature of method, it should be returned, current mininmum is first item
    for(size_t i = 0; i < size; i++) { // from first item to last item, size_t is a good type from examples
        if (array[i] < * minimum) minimum = array + i; // if value in a cell by pointer less than current minumum
    }
    return minimum;
}