#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list {
    char *data;
    struct linked_list *next;
} linked_list;

void free_linkedlist(linked_list *node) {
    if(node->next != NULL) {
        free_linkedlist(node->next);
    }
    free(node->data);
    free(node);
}

void print_linkedlist(linked_list *node) {
    printf("addr:<| %p |> - data:<| %s |>\n",node, node->data);
    while(node->next != NULL) {
        node = node->next;
        printf("addr:<| %p |> - data:<| %s |>\n",node, node->data);
    
    }
}

linked_list *add_to_linkedlist(linked_list *parent, char *data) {
    linked_list *node = malloc(sizeof(linked_list));
    node->next = NULL;
    if(data != NULL) { node->data = data; }
    else { node->data = NULL; }
    if(parent != NULL) {
        while(parent->next != NULL) { parent = parent->next; }
        parent->next = node;
    }
     return node;
}


linked_list *get_user_input() {
    linked_list *node = add_to_linkedlist(NULL, NULL);
    linked_list *parent = node;
    int count = 0;
    char ac_char;
     while(1) {
        ac_char = getchar();
        if(ac_char == '\n') { break; }
        if(ac_char == ' ') {
            if(count > 0) {
                node = add_to_linkedlist(parent, NULL);
                count = 0;
            }
        } else {
            char *new = realloc(node->data, (count + 1) * sizeof(char));
            node->data = new;
            node->data[count] = ac_char;
            count++;
        }
    };
    return parent;
}

int main(void) {

    linked_list *node = get_user_input();
    print_linkedlist(node);
    free_linkedlist(node);
}