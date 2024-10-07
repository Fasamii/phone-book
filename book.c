#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list {
    char *data;
    struct linked_list *next;
} linked_list;

linked_list *add_to_linkedlist(linked_list *parent, char *data) {
    linked_list *node = malloc(sizeof(linked_list));
    node->next = NULL;
    if(data != NULL) { 
        node->data = data;
        while(parent->next != NULL) { parent = parent->next; }
        parent->next = node;
    } else {
        node->data == NULL;
        return node;
    }
}

void free_linkedlist(linked_list *node) {
    if(node->next != NULL) {
        free_linkedlist(node->next);
    }
    free(node);
}

void print_linkedlist(linked_list *node) {
    node = node->next;
    printf("addr:<| %p |> - data:<| %s |>\n",node, node->data);
    while(node->next != NULL) {
        node = node->next;
        printf("addr:<| %p |> - data:<| %s |>\n",node, node->data);
    }
}

linked_list *get_user_input() {
    linked_list *parent = add_to_linkedlist(NULL, NULL);
    char ac_chgar = getchar();
    char *ac_command = malloc(100 * sizeof(char));
    for(int i = 0; ac_chgar != '\n'; i++) {
        if(ac_chgar == ' ') {
            int count = 0;
            for(int i = 0; ac_command[i] != ' ' && ac_command[i] != '\0'; i++) {
                count++;
            }
            char *str = malloc(count * sizeof(char));
            strcpy(str, ac_command);
            add_to_linkedlist(parent, str);
            for(int i = 0; ac_command[i] != '\0'; i++) {
                ac_command[i] = ' ';
            }
            i = 0;
            ac_chgar = getchar();
        } else {
            ac_command[i] = ac_chgar;
            ac_chgar = getchar();
        }
    }
    return parent;
}

int main(void) {

    linked_list *node = get_user_input();
    print_linkedlist(node);
    free_linkedlist(node);
}