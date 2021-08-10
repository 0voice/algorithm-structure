#include <stdlib.h>
#include <stdio.h>
#include "splay_tree.h"

SplayTree MakeEmpty(SplayTree T)
{
    if(T!=NULL){
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}
Position Find_value(ElementType X,SplayTree T)
{
    if(T==NULL){
        return NULL;
    }else if(X<T->element){
        return Find_value(X,T->Left);
    }else if(X>T->element){
        return Find_value(X,T->Right);
    }
    return T;
}
SplayTree SingleRotateWithLeft(SplayTree T)
{
    Position P=T->Left,Parent=T->Parent;
    T->Left=P->Right;
    P->Right=T;
    P->Parent=Parent;
    T->Parent=P;
    if(Parent!=NULL){
        if(Parent->Left==T){
            Parent->Left=P;
        }else if(Parent->Right==T){
            Parent->Right=P;
        }
    }
    return P;
}
SplayTree SingleRotateWithRight(SplayTree T)
{
    Position P=T->Right,Parent=T->Parent;
    T->Right=P->Left;
    P->Left=T;
    P->Parent=Parent;
    T->Parent=P;
    if(Parent!=NULL){
        if(Parent->Left==T){
            Parent->Left=P;
        }else if(Parent->Right==T){
            Parent->Right=P;
        }
    }
    return P;
}
SplayTree DoubleRotateWithLeft(SplayTree T)
{
    SingleRotateWithRight(T->Left);
    return SingleRotateWithLeft(T);
}
SplayTree DoubleRotateWithRight(SplayTree T)
{
    SingleRotateWithLeft(T->Right);
    return SingleRotateWithRight(T);
}
void Rotate_Zig_Zig(SplayTree T)
{
    Position P;
    P=SingleRotateWithLeft(T);
    SigleRotateWithLeft(P);
}
void Rotate_Zag_Zag(SplayTree T)
{
    Position P;
    P=SingleRotateWithRight(T);
    SingleRotateWithRight(P);
}
void Rotate_With_GrandPa(SplayTree T,Position P)
{
    Position Parent=P->Parent,GrandPa=P->Parent->Parent;
    if(GrandPa->Left==Parent){
        if(Parent->Left==P){
            Rotate_Zig_Zig(GrandPa);
        }else if(Parent->Right==P){
            DoubleRotateWithLeft(GrandPa);
        }
    }else if(GrandPa->Right==Parent){
        if(Parent->Left==P){
            DoubleRotateWithRight(GrandPa);
        }else if(Parent->Right==P){
            Rotate_Zag_Zag(GrandPa);
        }
    }
}
SplayTree Splay_Tree(SplayTree T,Position P)
{
    while(T->Left!=P&&T->Right!=P){
        Rotate_With_GrandPa(T,P);
    }
    if(T->Left==P){
        return SingleRotateWithLeft(T);
    }else{
        return SingleRotateWithRight(T);
    }
}
Position Find(ElementType X,SplayTree T)
{
    Position P;
    P=Find_value(X,T);
    if(P!=NULL&&P->Parent!=T){
        Splay_Tree(T,P);
    }
    return P;
}
SplayTree Insert(ElementType X,SplayTree T)
{
    Position temp;
    if(T==NULL){
        T=malloc(sizeof(struct Node));
        if(T==NULL){
            printf("out of space");
            exit(1);
        }else{
            T->Left=T->Right=T->Parent=NULL;
        }
    }else if(X<T->element){
        temp=Insert(X,T->Left);
        temp->Parent=T;
        T->Left=temp;
    }else if(X>T->element){
        temp=Insert(X,T->Right);
        temp->Parent=T;
        T->Right=temp;
    }
    return T;
}
SplayTree Delete(ElementType X,SplayTree T)
{
    Position P,temp;
    P=Find(X,T);
    if(P!=NULL){
        if(P->Left==NULL&&P->Right==NULL){
            free(P);
            return NULL;
        }else if(P->Left==NULL){
            temp=P->Right;
            free(P);
            return temp;
        }else if(P->Right==NULL){
            temp=P->Left;
            free(P);
            return temp;
        }else{
            temp=FindMin(P->Right);
            P->element=temp->element;
            temp->Parent->Left=NULL;
            free(temp);
            return P;
        }
    }
    return NULL;
}
