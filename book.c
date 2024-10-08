#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list {
    char *data;
    struct linked_list *next;
} linked_list;

void free_linkedlist(linked_list *node) {
    linked_list *temp;
    while(node != NULL) {
        temp = node->next;
        free(node->data);
        free(node);
        node = temp;
    }
    return;
}

void print_linkedlist(linked_list *node) {
    while(node != NULL) {
        printf("addr:<| %p |> - data:<| %s |>\n",node, node->data);
        node = node->next;
    }
    return;
}

linked_list *get_user_input() {
    linked_list *node = malloc(sizeof(linked_list));
    if(node == NULL) { free(node); return NULL; }
    linked_list *parent = node;
    int count = 0;
    char ac_char;
    while((ac_char = getchar()) != '\n') {
        if(ac_char != ' ') {
            node->data = realloc(node->data, (count + 1) * sizeof(char));
            node->data[count++] = ac_char;
        } else if(count > 0) {
            node = node->next = malloc(sizeof(linked_list));
            if(node == NULL) { free_linkedlist(parent); return NULL; }
            node->next = NULL;
            node->data = NULL;
            count = 0;
        }
    }
    return parent;
}

int main(void) {

    linked_list *node = get_user_input();
    if(node != NULL) {
        print_linkedlist(node);
        free_linkedlist(node);
        return 0;
    }
    return -1;
}