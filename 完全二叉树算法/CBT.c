/**
*
* 完全二叉树结构的基本特征
* （1）在一个树结构中，有且仅有一个节点没有直接前驱，这个节点就是树的根节点；
* （2）除了根节点外，其余结个节点有且仅有一个直接前驱；
* （3）每个结点都可以有任意多个直接后继；
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAXLEN 20
typedef char DATA;
typedef struct CBT
{
    DATA data;
    struct CBT *left;
    struct CBT *right;
}CBTType;

CBTType *initTree()
{
    CBTType *node;
    if (node=(CBTType *)malloc(sizeof(CBTType)))
    {
        printf("please input the root! \n");
        scanf("%s",&node->data);
        node->left=NULL;
        node->right=NULL;
        if (node!=NULL)
        {
            return node;
        }
        else
            return NULL;

    }
    return NULL;
}


//查询节点是否存在
CBTType *Treefindnode(CBTType *treeNode,DATA data)
{


    if (treeNode==NULL)
    {
        return NULL;
    }
    else
    {
        if (treeNode->data==data)
        {
            return treeNode ;
        }
        else
        {
            if (treeNode=Treefindnode(treeNode->left,data))
            {
                return treeNode;
            }
            else if (treeNode=Treefindnode(treeNode->right,data))
            {
                return treeNode;
            }
            else
                return NULL;
        }
    }
}

//增加结点

void AddTreeNode(CBTType *treeNode)
{
    CBTType *pnode,*parent;
    DATA data;
    char flag;
    if (pnode=(CBTType*)malloc(sizeof(CBTType)))
    {
        printf("input the node data \n");
        fflush(stdin);
        scanf("%s",&pnode->data);
        pnode->left=NULL;
        pnode->right=NULL;

        printf("input the node's parent node\n");
        fflush(stdin);
        scanf("%s",&data);
        parent=Treefindnode(treeNode,data);
        if (!parent)
        {
            printf("can't find the parent node!\n");
            free(pnode);
            return ;
        }
        printf("1.add to the left node!\n2.add to the right node!");
        do
        {
            flag=getch();
            flag-='0';
            if (flag==1||flag==2)
            {
                if (parent==NULL)
                {
                    printf("no parent node,please give parent node first!\n");
                }
                else
                {
                    switch(flag)
                    {
                        case 1:  //添加到左节点
                            if (parent->left)  //左节点不为空
                            {
                                printf("the lefe node is not empty!\n");
                            }
                            else
                            {
                                parent->left=pnode;
                            }
                            break;
                        case 2:
                            if (parent->right)
                            {
                                printf("the right node is not empty!\n");
                            }
                            else
                                parent->right=pnode;
                            break;
                        default:
                            printf("useless parameter!\n");
                    }
                }
            }
        }while(flag!=1&&flag!=2);

    }
}


//获得左子树
CBTType *Treeleftnode(CBTType *treeNode)
{
    if (treeNode)
    {
        return treeNode->left;
    }
    else
        return NULL;
}


//获得右子树
CBTType *Treerightnode(CBTType *treeNode)
{
    if (treeNode)
    {
        return treeNode->right;
    }
    else
        return NULL;
}


//判断空树
int Treeisempty(CBTType *TreeNode)
{
    if(TreeNode)
        return 0;
    else
        return 1;
}

//计算二叉树的深度
int Treedepth(CBTType *treeNode)
{
    int depleft,depright;
    if (treeNode==NULL)
    {
        return 0;
    }
    else
    {
        depleft=Treedepth(treeNode->left);
        depright=Treedepth(treeNode->right);
        if (depleft>depright)
        {
            return depleft+1;
        }
        else
            return depright+1;
    }
}

//清空二叉树
void ClearTree(CBTType *treeNode)
{
    if (treeNode)
    {
        ClearTree(treeNode->left);
        ClearTree(treeNode->right);
        free(treeNode);
        treeNode=NULL;
    }
}

//显示节点数据
void display(CBTType *p)
{
    printf("%c",p->data);
}

//二叉树的遍历
//层次遍历
void levelTree(CBTType *treeNode)
{
    CBTType *q[MAXLEN];
    int head=0,tail=0;
    if (treeNode)
    {
        tail=(tail+1)%MAXLEN;
        q[tail]=treeNode;
    }
    while(head!=tail)
    {
        head=(head+1)%MAXLEN;
        treeNode=q[head];
        if (treeNode->left!=NULL)
        {
            tail=(tail+1)%MAXLEN;
            q[tail]=treeNode->left;
        }
        if (treeNode->right!=NULL)
        {
            tail=(tail+1)%MAXLEN;
            q[tail]=treeNode->right;
        }
    }
}


//先序遍历，中序遍历和后序遍历
void dlrTree(CBTType *p)
{
    if(p)
    {
        printf("%c\n", p->data);
        dlrTree(p->left);
        dlrTree(p->right);
    }
}

void ldrTree(CBTType *p)
{
    if(p)
    {
        dlrTree(p->left);
        printf("%c\n", p->data);
        dlrTree(p->right);
    }
}

void lrdTree(CBTType *p)
{
    if(p)
    {
        dlrTree(p->left);
        dlrTree(p->right);
        printf("%c\n", p->data);
    }
}


int main()
{
    CBTType *root=NULL;
    char flag1;
    char flag2;
    root =initTree();
    do{
        printf("please chose option to add node!\n");
        printf("0.quit\t");
        printf("1.add the bitree node.\n");
        flag1=getch();
        switch(flag1)
        {
            case '1':
                AddTreeNode(root);
                break;
            case '0':
                break;
            default:
                ;
        }

    }while(flag1!='0');


    do{
        printf("please chose the method to travese the tree,input 0 means quit!\n");
        printf("1.xian xu bian li\t");
        printf("2.zhong xu bian li\n");
        printf("3.xian xu bian li\t");
        printf("4.ceng ci bian li\n");
        flag2=getch();
        switch(flag2)
        {
            case '0':
                break;
            case '1':
                printf("the answer of dlrTree travese:\n");
                dlrTree(root);
                printf("\n");
                break;
            case '2':
                printf("the answer of ldrTree travese:\n");
                ldrTree(root);
                printf("\n");
                break;
            case '3':
                printf("the answer of lrdTree travese:\n");
                lrdTree(root);
                printf("\n");
                break;
            case '4':
                printf("the answer of levelTree travese:\n");
                levelTree(root);
                printf("\n");
                break;
            default:
                ;
        }
    }while(flag2!='0');

    printf("the depth of the tree is:%d\n", Treedepth(root));
    ClearTree(root);
    root=NULL;
}
