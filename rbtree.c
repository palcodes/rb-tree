#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BLACK   "\x1b[34m" // Using blue for better visibility on dark terminals

Node* createNode(RBTree *tree, int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = tree->NIL;
    node->right = tree->NIL;
    node->parent = tree->NIL;
    return node;
}

RBTree* createRBTree() {
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    tree->NIL = (Node*)malloc(sizeof(Node));
    tree->NIL->color = BLACK;
    tree->NIL->data = 0;
    tree->root = tree->NIL;
    return tree;
}

void leftRotate(RBTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->NIL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTree *tree, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->NIL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void insertFixup(RBTree *tree, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RBTree *tree, int data) {
    Node *z = createNode(tree, data);
    Node *y = tree->NIL;
    Node *x = tree->root;
    while (x != tree->NIL) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == tree->NIL) tree->root = z;
    else if (z->data < y->data) y->left = z;
    else y->right = z;
    insertFixup(tree, z);
}

void rbTransplant(RBTree *tree, Node *u, Node *v) {
    if (u->parent == tree->NIL) tree->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void deleteFixup(RBTree *tree, Node *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void deleteNodeInternal(RBTree *tree, Node *z) {
    Node *y = z;
    Node *x;
    NodeColor y_orig = y->color;
    if (z->left == tree->NIL) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = findMin(tree, z->right);
        y_orig = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_orig == BLACK) deleteFixup(tree, x);
    free(z);
}

void deleteNode(RBTree *tree, int data) {
    Node *z = search(tree, data);
    if (z != tree->NIL) deleteNodeInternal(tree, z);
}

Node* search(RBTree *tree, int data) {
    Node *x = tree->root;
    while (x != tree->NIL && data != x->data) {
        if (data < x->data) x = x->left;
        else x = x->right;
    }
    return x;
}

Node* findMin(RBTree *tree, Node *x) {
    if (x == tree->NIL) return x;
    while (x->left != tree->NIL) x = x->left;
    return x;
}

Node* findMax(RBTree *tree, Node *x) {
    if (x == tree->NIL) return x;
    while (x->right != tree->NIL) x = x->right;
    return x;
}

void deleteMin(RBTree *tree) {
    Node *m = findMin(tree, tree->root);
    if (m != tree->NIL) deleteNodeInternal(tree, m);
}

void deleteMax(RBTree *tree) {
    Node *m = findMax(tree, tree->root);
    if (m != tree->NIL) deleteNodeInternal(tree, m);
}

void visualPrint(RBTree *tree, Node *root, int indent) {
    if (root != tree->NIL) {
        visualPrint(tree, root->right, indent + 8);
        for (int i = 0; i < indent; i++) printf(" ");
        if (root->color == RED)
            printf(COLOR_RED "(%d)" COLOR_RESET "\n", root->data);
        else
            printf(COLOR_BLACK "(%d)" COLOR_RESET "\n", root->data);
        visualPrint(tree, root->left, indent + 8);
    }
}
