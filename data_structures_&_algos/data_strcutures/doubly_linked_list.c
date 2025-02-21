#include <stdio.h>
#include <stdlib.h>


typedef struct DLL_Node {
    int value;
    struct DLL_Node* next;
    struct DLL_Node* previous;
} DLL_Node;

typedef struct {
    DLL_Node* head;
    DLL_Node* tail;
} DLL;

DLL_Node* DLL_create_node(int value){
    DLL_Node* newNode = (DLL_Node*) malloc(sizeof(DLL_Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

void DLL_list_init(DLL* List){
    List->head = NULL;
    List->tail = NULL;
    return;
}

int DLL_get_length(DLL* List){
    if(List->head == NULL){
        return 0;
    }
    int l = 1;
    DLL_Node* current = List->head->next;
    while(current != NULL){
        l++;
        current = current->next;
    }
    return l;
};

void DLL_insert(DLL* List, int index, int value){
    if (index == 0){
        DLL_Node* newNode = DLL_create_node(value);
        newNode->next = List->head;
        if(DLL_get_length(List) == 0){
            List->tail = newNode;
        } else if(DLL_get_length(List) == 1){
            List->tail->previous = newNode;
        } else if (DLL_get_length(List) > 1){
            List->head->next->previous = newNode;
        }
        List->head = newNode;
        
        return;
    }
    if (index == 1){
        DLL_Node* newNode = DLL_create_node(value);
        newNode->next = List->head->next;
        if(DLL_get_length(List) == 1){
            List->tail = newNode;
        } else if (DLL_get_length(List) == 2){
            List->tail->previous = newNode;
        } else if (DLL_get_length(List) > 2){
            List->head->next->next->previous = newNode;
        }
        List->head->next = newNode;
        newNode->previous = List->head;
        return;
    }
    DLL_Node* current = List->head->next;
    //loop to specified index -1 
    for(int i = 1; i < index - 1; i++){
        if (current == NULL){
            return;
        }
        current = current->next;
    }
    DLL_Node* newNode = DLL_create_node(value);
    newNode->next = current->next;
    newNode->previous = current;
    current->next = newNode;
    return;
};

void DLL_append(DLL* List, int value){
    DLL_Node* newNode = DLL_create_node(value);
    if (List->head == NULL){
        List->head = newNode;
        List->tail = newNode;
        return;
    }
    List->tail->next = newNode;
    newNode->previous = List->tail;
    List->tail = newNode;
    return;
};

int DLL_contains(DLL* List, int value){
    DLL_Node* current = List->head;
    int i = 0;
    while(current != NULL){
        if(current->value == value){
            return i;
        } else {
            i++;
            current = current->next; 
        }
    }
    return -1;
};

void DLL_remove(DLL* List, int index){
    if (index == 0){
        List->head = List->head->next;
        return;
    }
    DLL_Node* current = List->head;
    for (int i = 0; i < index -1; i++){
        if(current == NULL){
            return;
        }
        current = current->next;
    }
    current->next = current->next->next;
    return;
};

void DLL_print(DLL* List){
    DLL_Node* current = List->head;
    while (current != NULL){
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
    return;
}

void DLL_print_reverse(DLL* List){
    DLL_Node* current = List->tail;
    while (current != NULL){
        printf("%d -> ", current->value);
        current = current->previous;
    }
    printf("NULL\n");
    return;
}


int main(){
    DLL test_list;
    DLL_list_init(&test_list);
    DLL_insert(&test_list, 0, 2);
    DLL_insert(&test_list, 0, 1);
    DLL_insert(&test_list, 1, 5);
//    DLL_append(&test_list, 10);
    DLL_print(&test_list);
    int x = DLL_get_length(&test_list);
    printf("%d\n", x);
    DLL_print_reverse(&test_list);
    DLL_append(&test_list, 33);
    DLL_print(&test_list);
    int y = DLL_contains(&test_list, 5);
    printf("%d\n", y);
    return 0;
}

