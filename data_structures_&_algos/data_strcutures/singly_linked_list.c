#include <stdio.h>
#include <stdlib.h>

typedef struct SLL_Node {
    int value;
    struct SLL_Node* next;
} SLL_Node;

typedef struct {
    SLL_Node* head;
} SLL;

SLL_Node* SLL_create_node(int value){
    SLL_Node* newNode = (SLL_Node*) malloc(sizeof(SLL_Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void SLL_list_init(SLL* List){
    List->head = NULL;
    return;
}


void SLL_insert(SLL* List, int index, int value){
    if (index == 0){
        SLL_Node* newNode = SLL_create_node(value);
        newNode->next = List->head;
        List->head = newNode;
        return;
    }
    if (index == 1){
        SLL_Node* newNode = SLL_create_node(value);
        newNode->next = List->head->next;
        List->head->next = newNode;
        return;
    }
    SLL_Node* current = List->head->next;
    //loop to specified index -1 
    for(int i = 1; i < index - 1; i++){
        if (current == NULL){
            return;
        }
        current = current->next;
    }
    SLL_Node* newNode = SLL_create_node(value);
    newNode->next = current->next;
    current->next = newNode;
    return;
};

void SLL_append(SLL* List, int value){
    SLL_Node* newNode = SLL_create_node(value);
    if (List->head == NULL){
        List->head = newNode;
        return;
    }
    SLL_Node* current = List->head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
    return;
};

void SLL_contains(){

};

int SLL_get_length(){
    return 0;
};

void SLL_remove(){

};

void SLL_print(SLL* List){
    SLL_Node* current = List->head;
    while (current != NULL){
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
    return;
}

int main(){
    SLL test_list;
    SLL_list_init(&test_list);
    SLL_insert(&test_list, 0, 2);
    SLL_insert(&test_list, 0, 1);
    SLL_insert(&test_list, 1, 5);
    SLL_print(&test_list);
    return 0;
}

