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
    free(node->data);
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
    int count = 0;
    while(1) {
        if(ac_chgar == ' ' || ac_chgar == '\n') {
            char *str = malloc(count * sizeof(char));
            strcpy(str, ac_command);
            add_to_linkedlist(parent, str);
            if(ac_chgar == '\n') { 
                free(ac_command);    
                return parent; 
            }
            for(int i = 0; i < count; i++) {
                ac_command[i] = '\0';
            }
            count = 0;
            ac_chgar = getchar();

        } else {
            ac_command[count] = ac_chgar;
            count++;
            ac_chgar = getchar();
        }
    }
    return parent;
}

int get_operation_num(linked_list *parent) {
    return 0;
}

void search() {
    printf("-searching-\n");
}

void add_contact() {
    printf("-adding-\n");
}

int main(void) {

    linked_list *node = get_user_input();
    print_linkedlist(node);
 
    switch(get_operation_num(node)) {
        case 0: search(); break;
        case 1: add_contact(); break;
    }

    free_linkedlist(node);
}