/* Вы можете пользоваться этими функциями из предыдущих заданий */
size_t read_size() { size_t i; scanf("%zu", &i); return i; }

void array_int_fill( int64_t* array, size_t sz );

struct array_int array_int_read();
struct maybe_int64 array_int_get( struct array_int a, size_t i );
bool array_int_set( struct array_int a, size_t i, int64_t value );
void array_int_print( struct array_int array );
struct maybe_int64 array_int_min( struct array_int array );
void array_int_free( struct array_int a );

void array_int_normalize( struct array_int array, int64_t m ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    array.data[i] = array.data[i] - m;
  }
}

/*  ---- maybe int[] ---- */

struct maybe_array_int {
  struct array_int value;
  bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
  return (struct maybe_array_int) { array, true };
}
const struct maybe_array_int none_array_int = { {NULL, 0}, false };


/*  ---- int[][] ---- */

struct array_array_int {
  struct array_int* data;
  size_t size;
};

/*  --- строки ---  */

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
  if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
  else { return none_array_int; }
}

bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
  if (0 <= i && i < a.size) {
    a.data[i] = value;
    return true;
  }
  else { return false; }
}

/*  --- get/set ---  */

struct maybe_int64 array_array_int_get(struct array_array_int a, size_t i, size_t j) {
    struct maybe_array_int row_of_array = array_array_int_get_row(a, i);
    // I found ternar operator for realizing simple logic of this function
    return (!row_of_array.valid) ? (struct maybe_int64) {0} : array_int_get(row_of_array.value, j);
}

bool array_array_int_set(struct array_array_int a, size_t i, size_t j, int64_t value) {
    struct maybe_array_int row_of_array = array_array_int_get_row(a, i);
    return (!row_of_array.valid) ? false : array_int_set(row_of_array.value, j, value);
}


/*  --- read/print ---  */

struct array_array_int array_array_int_read() {
    struct array_array_int readable_array = {.size = read_size(), .data = NULL};
    // if array is not empty
    if (readable_array.size > 0) {
        readable_array.data = malloc(sizeof(struct array_int) * readable_array.size); // allocate memory for each                                                                                            cell of array
        for (size_t index = 0; index < readable_array.size; index++) {
            readable_array.data[index] = array_int_read(); // read cell using old functinon and save to                                                                           array.data[index]
        }
        return readable_array;
    } else return readable_array;
}


void array_array_int_print( struct array_array_int array) {
    for (size_t index = 0; index < array.size; index++) {
        struct maybe_array_int row_of_array = array_array_int_get_row(array, index);
        if (row_of_array.valid) {
            array_int_print(row_of_array.value); // print row of array and \n or only \n if nothing to print in row
            printf("\n");
        } else printf("\n");
    }
}


/*  --- min/normalize ---  */

// найти минимальный элемент в массиве массивов
struct maybe_int64 array_array_int_min(struct array_array_int array) {
    struct maybe_int64 final_minimum = {0};
    for (size_t index = 0; index < array.size; index++) {
        struct maybe_int64 current_minimum = array_int_min(array.data[index]);
        if (current_minimum.valid) { // if this number is ok
            // current minimum is absolute minimum if is lower then prev absolute minumum or absolute minium is not                defined (unsuccessful initialization)
            if (!final_minimum.valid || final_minimum.value > current_minimum.value) {
                final_minimum = current_minimum;
            }
        }
    }
    return final_minimum;
}

// вычесть из всех элементов массива массивов число m
void array_array_int_normalize( struct array_array_int array, int64_t m) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
    if (cur_row.valid) {
         array_int_normalize( cur_row.value, m );
    }
  }
}

void array_array_int_free(struct array_array_int array) {
  for (size_t index = 0; index < array.size; index++) { // move from row to row
      array_int_free(array.data[index]); // delete it using old function because row is one-dimensional array
  }
  free(array.data);
}