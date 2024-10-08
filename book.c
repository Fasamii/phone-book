#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct input {
    char *data;
    short type;
    struct input *next;
} input;

void free_linkedlist(input *node) {
    input *temp;
    while(node != NULL) {
        temp = node->next;
        free(node->data);
        free(node);
        node = temp;
    }
    return;
}

void print_linkedlist(input *node) {
    while(node != NULL) {
        printf("addr:<| %p |> - data:<| %s |>\n",node, node->data);
        node = node->next;
    }
    return;
}

short get_type(input *node) {
    
}

input *get_user_input() {
    input *node = malloc(sizeof(input));
    if(node == NULL) { free(node); return NULL; }
    input *parent = node;
    int count = 0;
    char ac_char;
    while((ac_char = getchar()) != '\n') {
        if(ac_char != ' ') {
            node->data = realloc(node->data, (count + 1) * sizeof(char));
            node->data[count++] = ac_char;
        } else if(count > 0) {
            node = node->next = malloc(sizeof(input));
            if(node == NULL) { free_linkedlist(parent); return NULL; }
            node->next = NULL;
            node->data = NULL;
            count = 0;
        }
    }
    return parent;
}

int main(void) {

    input *node = get_user_input();
    if(node == NULL) { return -1; }
    print_linkedlist(node);
    free_linkedlist(node);
    return 0;
}