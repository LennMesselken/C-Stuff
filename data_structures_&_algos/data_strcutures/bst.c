#include <stdio.h>
#include <stdlib.h>

typedef struct BST_Node{
    int value;
    struct BST_Node* left;
    struct BST_Node* right;
} BST_Node;

typedef struct {
    BST_Node* root;
} BST;

void BST_init(BST* Tree){
    Tree->root = NULL;
    return;
}

BST_Node* BST_create_node(int value){
    BST_Node* newNode = (BST_Node*) malloc(sizeof(BST_Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void BST_insert(BST* Tree, int value){
    BST_Node* newNode = BST_create_node(value);
    if (Tree->root == NULL){
        Tree->root = newNode;
        return;
    }
    BST_Node* leading, trailing;
    leading = Tree->root;
    while (leading != NULL){
        trailing = *leading;
        if (value < leading->value){
            leading = leading->left;
            continue;
        } else {
            leading = leading->right;
            continue;
        }
    }

    if (value < trailing.value){
        trailing.left = newNode;
    } else {
        trailing.right = newNode;
    }
    return;
}



void BST_print(BST* Tree){
    BST_Node* current = Tree->root;
    while(current != NULL){
        printf("%d >left> ", current->value);
        current = current->left;
    }
    printf("\n");
    return;
    
    
}

int main(){
    BST test_tree;
    BST_init(&test_tree);
    BST_print(&test_tree);
    BST_insert(&test_tree, 10);
    BST_print(&test_tree);
    BST_insert(&test_tree, 5);
    BST_print(&test_tree);
    BST_insert(&test_tree, 2);
    BST_print(&test_tree);

}


