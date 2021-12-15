enum move_dir {MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE};

// structure for describing callbacks
struct move_callback_node {
   void (*function) (enum move_dir); // movement
   struct move_callback_node* next_callback; // link to new callback
};

// same function was wtitten in previous tasks
struct move_callback_node* create_new_node( void (*function) (enum move_dir)) { // create new node
  struct move_callback_node* new_node = malloc(sizeof(struct move_callback_node));
    if (new_node != NULL) {
        new_node -> function = function; // funciton value
        new_node -> next_callback = NULL; // new link value is link to null, because is new element
    }
    return new_node;
}


// I love copy-past-update from previous tasks :)
void add_new_callback_to_front(struct move_callback_node** old_node, void (*function) (enum move_dir) ) {
    struct move_callback_node* new_node = create_new_node(function);
    if (new_node != NULL) {
        new_node -> next_callback = *old_node;
        *old_node = new_node;
    }
}

// get length of list, it will be necessary in future
size_t get_length_of_callbacks_list(const struct move_callback_node* list_of_callbacks) {
    size_t length_of_list = 0;
    while(list_of_callbacks != NULL) {
        list_of_callbacks = list_of_callbacks -> next_callback;
        length_of_list++;
    }
    return length_of_list;
}

// copy-past again, get penultimate callback
struct move_callback_node* get_penultimate_callback_from_list(struct move_callback_node* list_of_callbacks) {
    struct move_callback_node* penultimate_callback = NULL;
    struct move_callback_node* last_callback = NULL;
    while(list_of_callbacks != NULL) {
        penultimate_callback = last_callback;
        last_callback = list_of_callbacks;
        list_of_callbacks = list_of_callbacks -> next_callback;
    }
    return penultimate_callback;
}

// thanks' me for ready code from previous tasks, delete last callback function
void delete_last_callback_from_list(struct move_callback_node** list_of_callbacks) {
    struct move_callback_node* penultimate_callback = get_penultimate_callback_from_list(*list_of_callbacks);
    if (penultimate_callback != NULL) {
        free(penultimate_callback -> next_callback); // delete penultimate callback
        penultimate_callback -> next_callback = NULL; // move last callback to penultimate position and delete from
                                                      // current position
    } else {
        free(*list_of_callbacks); // for special cases, when there are no penultimate callback
        *list_of_callbacks = NULL;
    }
}

// delete all callbacks
void delete_list_of_callbacks( struct move_callback_node* list_of_callbacks) {
    while(list_of_callbacks != NULL) {
        delete_last_callback_from_list(&list_of_callbacks);
    }
}

// fuction for finding last callback
struct move_callback_node* get_last_callback_from_list(struct move_callback_node* list_of_callbacks) {
    struct move_callback_node* last_callback = NULL;
    while(list_of_callbacks != NULL) {
        last_callback = list_of_callbacks;
        list_of_callbacks = list_of_callbacks -> next_callback;
    }
    return last_callback;
}

// adding callbacks to back
void add_new_callback_to_back(struct move_callback_node** old_callback, void (*function) (enum move_dir) ) {
    struct move_callback_node* last_callback = get_last_callback_from_list(*old_callback);
    struct move_callback_node* new_callback = create_new_node(function);
    if (last_callback != NULL)
        last_callback -> next_callback = new_callback;
    else
        *old_callback = new_callback;
}

// start callbacks list
void execute_callbacks(struct move_callback_node* callback, enum move_dir direction) {
    while(callback != NULL) {
        callback -> function(direction);
        callback = callback -> next_callback;
    }
}

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct robot {
    const char* name;
    struct move_callback_node* callbacks;
};

// Определите тип обработчика событий move_callback с помощью typedef
//???, later

// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, void (*new_callback) (enum move_dir)) {
    struct move_callback_node** start_callbacks = &(robot -> callbacks);
    add_new_callback_to_front(start_callbacks, new_callback);
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
    delete_list_of_callbacks(robot -> callbacks);
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir direction) {
    struct move_callback_node* start_callbacks = robot -> callbacks;
    execute_callbacks(start_callbacks, direction);
}