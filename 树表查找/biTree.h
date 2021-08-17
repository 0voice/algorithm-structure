#ifndef CHIYX_BITREE
#define CHIYX_BITREE
#ifndef NULL
#define NULL 0
#endif

typedef int DataType;
//二叉树的节点结构
typedef struct BiTreeNode {
    DataType data;
    struct BiTreeNode *parent;
    struct BiTreeNode *left;
    struct BiTreeNode *right;
}BiTreeNode, *BiTree;

//查找：返回第一个等于data域等于key的节点，不存在返回NULL
BiTreeNode *search(BiTree *biTree, DataType key);
//返回二叉树的最小节点,空树返回NULL
BiTreeNode *minImum(BiTree *biTree);
//返回二叉树的最大节点,空树返回NULL
BiTreeNode *maxImum(BiTree *biTree);
//返回节点x的后继节点,不存在后继（节点x为最大节点）返回NULL
BiTreeNode *successor(BiTreeNode *x);
//返回节点x的前驱节点，不存在前驱（节点x为最小节点）返回NULL
BiTreeNode *predecessor(BiTreeNode *x);
//将值data插入到二叉树中（生成一个值为data的节点）
void insertNode(BiTree *biTree, DataType data);
//删除一个值为data的节点
void deleteNode(BiTree *biTree, DataType data);
//中序遍历二叉树
void inorderTraversal(BiTree *biTree, void (*visitor)(BiTreeNode *node));

#endif
