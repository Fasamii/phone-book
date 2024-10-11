#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hash {
    struct hash *next[62];
    int num;
    char *name;
} hash;

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

char *get_user_input_s(char *message) {
    printf("(%s): ", message);
    char *data = malloc(sizeof(100));
    scanf("%s", data);
    return data;
}

int get_user_input_i(char *message) {
    printf("(%s): ", message);
    int data;
    scanf("%d", &data);
    return data;
}
int main(void) {
    hash *parent = malloc(sizeof(hash));
    char command = 'y';
    while(command) {
        printf("[phone book]>(a - for add | d - for del | s - for search): ");
        scanf("%c", &command);
        switch(command) {
            case 'a':
                add(parent, get_user_input_s("new name"), get_user_input_i("new number"));
            break;
            case 'd': free_table(parent); parent = malloc(sizeof(hash)); break;
            case 's': 
                char *name = get_user_input_s("name of number");
                hash *dest = search_by_name(parent, name);
                if(dest) {
                    printf("number of that name is <%i>\n", dest->num);
                } else {
                    printf("not found\n");
                }
            break;
            default: break;
        }
    }
    free_table(parent);
    return 0;
}