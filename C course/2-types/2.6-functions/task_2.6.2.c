// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct { char* addr; } string_heap ;

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};


struct user {
  const uid id;
  const string_heap name;
  enum city city;
};

// It's necessary now, I took it from previous tasks
size_t find_length_of_string(const char* string) {
    size_t length_of_string = 0;
    while(*string != 0) {
        length_of_string++;
        string++;
    }
    return length_of_string;
}

// It's necessary now, I took it from previous tasks
char* copy_string(const char* string) {
    size_t length_of_string = find_length_of_string(string);
    char* result = malloc(sizeof(char)*(length_of_string + 1));
    for (size_t index = 0; index <= length_of_string; index++) {
        result[index] = string[index];
    }
    return result;
}

// It's necessary now, I took it from previous tasks
// скопировать в кучу
string_heap halloc( const char* string) {
    return (string_heap) {.addr = copy_string(string)};
}
// It's necessary now, I took it from previous tasks
void heap_string_free( string_heap h ) {
    free(h.addr);
}

// comporator function for strings
int compare_strings(const string_heap a, const string_heap b) {
    char* first_string = a.addr;
    char* second_string = b.addr;
    return strcmp(first_string, second_string);
}

// comporator functions for cities
int compare_cities(enum city cityA, enum city cityB) {
    string_heap first_city = halloc(city_string[cityA]);
    string_heap second_city = halloc(city_string[cityB]);
    int result_of_comparing = compare_strings(first_city, second_city);
    // Not all dynamically allocated memory is freed - FREE IT HERE
    // i thought is not necessary
    heap_string_free(first_city);
    heap_string_free(second_city);
    return result_of_comparing;
}

// in previous solution a lot of bugs with types transformations
// maybe a lot of abstractions is a reason.
// now I try do it more simple, compare not numbers, compare users by numbers immidiatelly
int compare_users_by_id(const void* a, const void* b) {
    struct user first_user = *((struct user*) a);
    struct user second_user = *((struct user*) b);
    if (first_user.id > second_user.id)
        return 1;
    else if (first_user.id < second_user.id)
        return -1;
    else
        return 0;
}

int compare_users_by_name(const void* a, const void* b) {
    struct user first_user = *((struct user*) a);
    struct user second_user = *((struct user*) b);
    return compare_strings(first_user.name, second_user.name);
}

int compare_users_by_city(const void* a, const void* b) {
    struct user first_user = *((struct user*) a);
    struct user second_user = *((struct user*) b);
    return compare_cities(first_user.city, second_user.city);
}


/* Сортировать массив пользователей по полю uid по возрастанию */
void users_sort_uid(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), compare_users_by_id);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор 
   строк -- стандартную функцию strcmp */
void users_sort_name(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), compare_users_by_name);
}

/* Сортировать массив по _текстовому представлению_ города */
void users_sort_city(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), compare_users_by_city);
}