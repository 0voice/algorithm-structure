#include <stdio.h>
#include <stdlib.h>

typedef struct GLNode{
    int tag;//标志域
    union{
        char atom;//原子结点的值域
        struct{
            struct GLNode * hp,*tp;
        }ptr;//子表结点的指针域，hp指向表头；tp指向表尾
    };
}*Glist,GNode;

Glist creatGlist(Glist C){
    //广义表C
    C=(Glist)malloc(sizeof(GNode));
    C->tag=1;
    //表头原子‘a’
    C->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.hp->tag=0;
    C->ptr.hp->atom='a';
    //表尾子表（b,c,d）,是一个整体
    C->ptr.tp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->tag=1;
    C->ptr.tp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.tp=NULL;
    //开始存放下一个数据元素（b,c,d）,表头为‘b’，表尾为（c,d）
    C->ptr.tp->ptr.hp->tag=1;
    C->ptr.tp->ptr.hp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.hp->ptr.hp->tag=0;
    C->ptr.tp->ptr.hp->ptr.hp->atom='b';
    C->ptr.tp->ptr.hp->ptr.tp=(Glist)malloc(sizeof(GNode));
    //存放子表(c,d)，表头为c，表尾为d
    C->ptr.tp->ptr.hp->ptr.tp->tag=1;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->tag=0;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.hp->atom='c';
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp=(Glist)malloc(sizeof(GNode));
    //存放表尾d
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->tag=1;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp=(Glist)malloc(sizeof(GNode));
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->tag=0;
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.hp->atom='d';
    C->ptr.tp->ptr.hp->ptr.tp->ptr.tp->ptr.tp=NULL;
    return C;
}
void copyGlist(Glist C, Glist *T){
    //如果C为空表，那么复制表直接为空表 
    if (!C) {
        *T=NULL;
    }
    else{
        *T=(Glist)malloc(sizeof(GNode));//C不是空表，给T申请内存空间
        //申请失败，程序停止
        if (!*T) {
            exit(0);
        }
        (*T)->tag=C->tag;//复制表C的tag值
        //判断当前表元素是否为原子，如果是，直接复制
        if (C->tag==0) {
            (*T)->atom=C->atom;
        }else{//运行到这，说明复制的是子表
            copyGlist(C->ptr.hp, &((*T)->ptr.hp));//复制表头
            copyGlist(C->ptr.tp, &((*T)->ptr.tp));//复制表尾
        }
    }
}
int main(int argc, const char * argv[]) {
    Glist C=NULL;
    C=creatGlist(C);
    Glist T=NULL;
    copyGlist(C,&T);
    printf("%c",T->ptr.hp->atom);
    return 0;
}
