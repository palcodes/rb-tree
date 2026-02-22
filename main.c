#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define BORDER "=================================================="
#define SUB    "--------------------------------------------------"

void printHeader(const char* title) {
    printf("\n%s\n", BORDER);
    printf("  %s\n", title);
    printf("%s\n", BORDER);
}

int main() {
    RBTree *tree = createRBTree();
    int choice, value;
    Node *temp;

    while (1) {
        printHeader("RED-BLACK TREE COMMAND CENTER");
        printf(" 1. Insert Node            5. Find Maximum\n");
        printf(" 2. Delete Node            6. Delete Minimum\n");
        printf(" 3. Search Node            7. Delete Maximum\n");
        printf(" 4. Find Minimum           8. View Tree Structure\n");
        printf(" 0. Exit System\n");
        printf("%s\n", SUB);
        printf("Enter selection: ");

        if (scanf("%d", &choice) != 1) break;

        printf("\n");
        switch (choice) {
            case 1:
                printf("[ACTION] Enter value to insert: ");
                scanf("%d", &value);
                insert(tree, value);
                printf("[SUCCESS] Node %d inserted.\n", value);
                break;
            case 2:
                printf("[ACTION] Enter value to delete: ");
                scanf("%d", &value);
                if (search(tree, value) != tree->NIL) {
                    deleteNode(tree, value);
                    printf("[SUCCESS] Node %d deleted.\n", value);
                } else printf("[ERROR] Node not found.\n");
                break;
            case 3:
                printf("[ACTION] Search for: ");
                scanf("%d", &value);
                temp = search(tree, value);
                if (temp != tree->NIL)
                    printf("[FOUND] Value %d is %s.\n", value, temp->color == RED ? "RED" : "BLACK");
                else printf("[NOT FOUND] Value %d is not in tree.\n", value);
                break;
            case 4:
                temp = findMin(tree, tree->root);
                if (temp != tree->NIL) printf("[MINIMUM] %d (%s)\n", temp->data, temp->color == RED ? "RED" : "BLACK");
                else printf("[INFO] Tree is empty.\n");
                break;
            case 5:
                temp = findMax(tree, tree->root);
                if (temp != tree->NIL) printf("[MAXIMUM] %d (%s)\n", temp->data, temp->color == RED ? "RED" : "BLACK");
                else printf("[INFO] Tree is empty.\n");
                break;
            case 6:
                deleteMin(tree);
                printf("[SUCCESS] Minimum node removed.\n");
                break;
            case 7:
                deleteMax(tree);
                printf("[SUCCESS] Maximum node removed.\n");
                break;
            case 8:
                printf("[TREE VISUALIZATION]\n");
                printf("(Blue nodes = BLACK, Red nodes = RED)\n\n");
                visualPrint(tree, tree->root, 0);
                break;
            case 0:
                printf("System exiting...\n");
                exit(0);
            default:
                printf("[ERROR] Invalid selection.\n");
        }
    }
    return 0;
}
