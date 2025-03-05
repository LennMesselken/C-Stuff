#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a BST node
typedef struct BST_Node {
    int value;
    struct BST_Node* left;
    struct BST_Node* right;
} BST_Node;

// Define the BST structure
typedef struct {
    BST_Node* root;
} BST;

// Function declarations
void BST_init(BST* Tree);
BST_Node* BST_create_node(int value);
void BST_insert(BST* Tree, int value);
void BST_print(BST* Tree);
void BST_Node_print(BST_Node* node);

#endif // BST_H