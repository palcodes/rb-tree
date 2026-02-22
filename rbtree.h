#ifndef RBTREE_H
#define RBTREE_H

typedef enum { RED, BLACK } NodeColor;

typedef struct Node {
    int data;
    NodeColor color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *NIL;
} RBTree;

RBTree* createRBTree();
void insert(RBTree *tree, int data);
void deleteNode(RBTree *tree, int data);
Node* search(RBTree *tree, int data);
Node* findMin(RBTree *tree, Node *x);
Node* findMax(RBTree *tree, Node *x);
void deleteMin(RBTree *tree);
void deleteMax(RBTree *tree);
void visualPrint(RBTree *tree, Node *root, int indent);

#endif
