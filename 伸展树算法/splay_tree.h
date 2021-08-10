#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

struct Node;
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode SplayTree;
typedef PtrToNode Position;

SplayTree MakeEmpty(SplayTree T);
Position Find(ElementType X,SplayTree T);
Position FindMax(SplayTree T);
Position FindMin(SplayTree T);
SplayTree Insert(ElementType X,SplayTree T);
SplayTree Delete(ElementType X,SplayTree T);

#endif

struct Node
{
    ElementType element;
    PtrToNode Left;
    PtrToNode Right;
    PtrToNode Parent;
};
