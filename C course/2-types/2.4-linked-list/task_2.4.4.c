// this function is necessary for deleting last node (I suppose)
// find penultimate, and using it, find last and delete it, after that penultimate node is last,
// and repeat this schema more and more.
// I don't know why I'm writing this, but understanding is more easy for me using this :)
struct list* find_penultimate_node(struct list* list) {
    struct list* penultimate_node = NULL;
    struct list* last_node = NULL;
    while (list != NULL) {
        penultimate_node = last_node; // "save" value
        last_node = list; // now last_node is really last, bcs next link is link to null
        list = list -> next;
    }
    return penultimate_node;
}

// logical continuation of my thinking. Delete last -> penultimate is last -> delete penultimate
// else FREE IT ALL
void delete_last_node(struct list** list) {
    struct list* penultimate_node = find_penultimate_node(*list);
    if (penultimate_node != NULL) {
        free(penultimate_node -> next);
        penultimate_node -> next = NULL;
    } else {
        free(*list);
        *list = NULL;
    }
}

void list_destroy(struct list* list ) {
    while (list != NULL) {
        delete_last_node(&list);
    }
}