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

BST_Node* BST_create_node(int value){
    BST_Node* newNode = (BST_Node*) malloc(sizeof(BST_Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


