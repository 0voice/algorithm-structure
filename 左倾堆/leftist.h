#ifndef _LEFTIST_TREE_H_
#define _LEFTIST_TREE_H_

typedef int Type;

typedef struct _LeftistNode{
    Type   key;                    // 关键字(键值)
    int npl;                    // 零路经长度(Null Path Length)
    struct _LeftistNode *left;    // 左孩子
    struct _LeftistNode *right;    // 右孩子
}LeftistNode, *LeftistHeap;

// 前序遍历"左倾堆"
void preorder_leftist(LeftistHeap heap);
// 中序遍历"左倾堆"
void inorder_leftist(LeftistHeap heap);
// 后序遍历"左倾堆"
void postorder_leftist(LeftistHeap heap);

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int leftist_minimum(LeftistHeap heap, int *pval);
// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y);
// 将结点插入到左倾堆中，并返回根节点
LeftistNode* insert_leftist(LeftistHeap heap, Type key);
// 删除结点(key为节点的值)，并返回根节点
LeftistNode* delete_leftist(LeftistHeap heap);

// 销毁左倾堆
void destroy_leftist(LeftistHeap heap);

// 打印左倾堆
void print_leftist(LeftistHeap heap);

#endif
