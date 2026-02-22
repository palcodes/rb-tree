# Project Documentation: Red-Black Tree Implementation

## Technical Specification
This project implements a self-balancing binary search tree (Red-Black Tree) to ensure $O(\log n)$ operational complexity for dynamic sets. The implementation adheres to the following invariant properties:
*   Each node is assigned a color attribute: Red or Black.
*   The root and all NIL leaf nodes are Black.
*   Red nodes must have Black children (No consecutive Red nodes).
*   Black-height consistency: Every path from a node to descendant NIL nodes contains an identical number of Black nodes.

## Supported Operations
The system provides the following primitives:
*   **Insertion**: Standard BST insertion followed by `insertFixup` (recoloring and rotations).
*   **Deletion**: Node removal followed by `deleteFixup` to restore structural properties.
*   **Search**: $O(\log n)$ value retrieval.
*   **Extrema**: Retrieval and removal of minimum and maximum elements.
*   **Visualization**: Formatted CLI output representing tree hierarchy and node metadata.

## Data Structures
```c
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
```

## Build Instructions
The project is modularized into header, implementation, and driver files. 

**Compilation:**
```bash
gcc -Wall -Wextra -o rbtree_system main.c rbtree.c
```

**Execution:**
```bash
./rbtree_system
```

## Interface Overview
The command-line interface (CLI) provides a structured menu for tree manipulation. 
*   **Input**: Integer-based data entry.
*   **Output**: ANSI-coded terminal representation. 
    *   Red nodes: Displayed in Red.
    *   Black nodes: Displayed in Blue/Black.
*   **Balancing**: The system automatically triggers left/right rotations and recoloring upon any structural modification.

## 6. Implementation Notes
*   **Memory Management**: Utilizes dynamic allocation (`malloc`) and requires manual deallocation for nodes.
*   **Sentinel Nodes**: Employs a single `NIL` sentinel node to represent all leaf nodes, optimizing memory and simplifying boundary condition logic.
