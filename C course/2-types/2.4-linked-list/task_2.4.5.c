struct list* list_last( struct list * list ) {
  struct list* last_element = NULL;
    while (list != NULL) { // loop for moving using links beetween nodes
        last_element = list; 
        struct list* new_list = list -> next; // moving
        list = new_list;
    }
    return last_element;
}