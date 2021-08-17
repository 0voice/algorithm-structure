#include <stdio.h>
#include <stdlib.h>
#include "biTree.h"
#define N  10
void printNode(BiTreeNode *node);

int main(int argc, char *argv[]) {
    BiTreeNode *root;
    int i;

    root = NULL;
    int data[N] = {10, 23, 11, 98, 111, 87, 34, 11, 33, 8};
    for (i = 0; i < N; i++) {
        insertNode(&root, data[i]);
    }
    printf("before delete:\n");
    inorderTraversal(&root, printNode);
    printf("\n");
    deleteNode(&root, 11);
    deleteNode(&root, 8);
    printf("after delete:\n");
    inorderTraversal(&root, printNode);
    printf("\n");
    exit(0);
}
void printNode(BiTreeNode *node) {
    printf("%d\t", node->data);
}
