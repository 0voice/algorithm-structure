#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_

typedef int Type;

typedef struct _SkewNode{
    Type   key;                    // 关键字(键值)
    struct _SkewNode *left;    // 左孩子
    struct _SkewNode *right;    // 右孩子
}SkewNode, *SkewHeap;

// 前序遍历"斜堆"
void preorder_skewheap(SkewHeap heap);
// 中序遍历"斜堆"
void inorder_skewheap(SkewHeap heap);
// 后序遍历"斜堆"
void postorder_skewheap(SkewHeap heap);

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int skewheap_minimum(SkewHeap heap, int *pval);
// 合并"斜堆x"和"斜堆y"，并返回合并后的新树
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y);
// 将结点插入到斜堆中，并返回根节点
SkewNode* insert_skewheap(SkewHeap heap, Type key);
// 删除结点(key为节点的值)，并返回根节点
SkewNode* delete_skewheap(SkewHeap heap);

// 销毁斜堆
void destroy_skewheap(SkewHeap heap);

// 打印斜堆
void print_skewheap(SkewHeap heap);

#endif
