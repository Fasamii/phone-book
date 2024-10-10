#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct input {
    char *data;
    struct input *next;
} input;

typedef struct hash {
    struct hash *next[62];
    int num;
    char *name;
} hash;

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

void free_table(hash *parent) {
    for(int i = 0; i < 62; i++) {
        if(parent->next[i]) {
            free_table(parent->next[i]);
        }
    }
    free(parent);
}

char encode(char c) {
    if(c > 64) {
        if(c > 96) {
            return (c - 61);
        }
        return (c - 55);
    }
return (c - 48);
}

int add(hash *node, char *name, int num) {
    for(int i = 0, n = strlen(name); i < n; i++) {
        char index = encode(name[i]);
        if(!node->next[index]) {
            hash *new = malloc(sizeof(hash));
            node = node->next[index] = new;
        } else {
            node = node->next[index];
        }
    }
    if(!node->name) {
        node->name = name;
        node->num = num;
        return 0;
    }
    return 1;
}

hash *search_by_name(hash *node, char *name) {
    for(int i = 0, n = strlen(name); i < n; i++) {
        char index = encode(name[i]);
        if(node->next[index] == NULL) { return NULL; }
        else { 
            node = node->next[index];
        }
    }
    return node;
}

input *get_user_input() {
    input *node = malloc(sizeof(input));
    if(node == NULL) { free(node); return NULL; }
    input *parent = node;
    int count = 0;
    char ac_char;
    node->data = malloc(1);
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

char get_operation(input *node) {
    if(node->data[0] == 'q') return 'q';
    if(node->data[0] == '-') { return 'a'; }
    if(node->next) {
        return get_operation(node->next);
    }
    return 'f';
}

char *get_name(input *in) {
    return "fasami";
}

int main(void) {

    hash *parent = malloc(sizeof(hash));

    while(1) {
        printf("[phone book]$ ");
        input *node = get_user_input();
        if(node == NULL) { printf("INCORRECT INPUT\n"); break; }
        printf("operation < %c >\n", get_operation(node));
        switch (get_operation(node)) {
            case 'a': add(parent, get_name(node), 123); break;
            case 'f': printf("number of < %s > is < %i >\n", search_by_name(parent, get_name(node)), get_name(node)); break;
            case 'q': return 0; break;
        }
        if(node) { free_linkedlist(node); }
    }
    free_table(parent);
    return 0;
}