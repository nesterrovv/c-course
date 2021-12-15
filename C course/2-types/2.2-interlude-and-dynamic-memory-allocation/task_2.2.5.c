void marray_free( int64_t** marray, size_t rows ) {
    for (size_t i = 0; i < rows; i++) { // rows is amount of one-dimensional arrays
        free(*(marray+i));  // free each of them
    }
    free(marray); // free array at all
}