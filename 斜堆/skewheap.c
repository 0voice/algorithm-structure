#include <stdio.h>
#include <stdlib.h>
#include "skewheap.h"

/*
 * 前序遍历"斜堆"
 */
void preorder_skewheap(SkewHeap heap)
{
    if(heap != NULL)
    {
        printf("%d ", heap->key);
        preorder_skewheap(heap->left);
        preorder_skewheap(heap->right);
    }
}

/*
 * 中序遍历"斜堆"
 */
void inorder_skewheap(SkewHeap heap)
{
    if(heap != NULL)
    {
        inorder_skewheap(heap->left);
        printf("%d ", heap->key);
        inorder_skewheap(heap->right);
    }
}

/*
 * 后序遍历"斜堆"
 */
void postorder_skewheap(SkewHeap heap)
{
    if(heap != NULL)
    {
        postorder_skewheap(heap->left);
        postorder_skewheap(heap->right);
        printf("%d ", heap->key);
    }
}

/*
 * 交换两个节点的内容
 */
static void swap_skewheap_node(SkewNode *x, SkewNode *y)
{
    SkewNode tmp = *x;
    *x = *y;
    *y = tmp;
}

/*
 * 获取最小值
 *
 * 返回值：
 *    成功返回0，失败返回-1
 */
int skewheap_minimum(SkewHeap heap, int *pval)
{
    if (heap == NULL)
        return -1;

    *pval = heap->key;

    return 0;
}

/*
 * 合并"斜堆x"和"斜堆y"
 *
 * 返回值：
 *     合并得到的树的根节点
 */
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;

    // 合并x和y时，将x作为合并后的树的根；
    // 这里的操作是保证: x的key < y的key
    if(x->key > y->key)
        swap_skewheap_node(x, y);

    // 将x的右孩子和y合并，
    // 合并后直接交换x的左右孩子，而不需要像左倾堆一样考虑它们的npl。
    SkewNode *tmp = merge_skewheap(x->right, y);
    x->right = x->left;
    x->left  = tmp;

    return x;
}

/*
 * 新建结点(key)，并将其插入到斜堆中
 *
 * 参数说明：
 *     heap 斜堆的根结点
 *     key 插入结点的键值
 * 返回值：
 *     根节点
 */
SkewNode* insert_skewheap(SkewHeap heap, Type key)
{
    SkewNode *node;    // 新建结点

    // 如果新建结点失败，则返回。
    if ((node = (SkewNode *)malloc(sizeof(SkewNode))) == NULL)
        return heap;
    node->key = key;
    node->left = node->right = NULL;

    return merge_skewheap(heap, node);
}

/*
 * 取出根节点
 *
 * 返回值：
 *     取出根节点后的新树的根节点
 */
SkewNode* delete_skewheap(SkewHeap heap)
{
    SkewNode *l = heap->left;
    SkewNode *r = heap->right;

    // 删除根节点
    free(heap);

    return merge_skewheap(l, r); // 返回左右子树合并后的新树
}

/*
 * 销毁斜堆
 */
void destroy_skewheap(SkewHeap heap)
{
    if (heap==NULL)
        return ;

    if (heap->left != NULL)
        destroy_skewheap(heap->left);
    if (heap->right != NULL)
        destroy_skewheap(heap->right);

    free(heap);
}

/*
 * 打印"斜堆"
 *
 * heap       -- 斜堆的节点
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
static void skewheap_print(SkewHeap heap, Type key, int direction)
{
    if(heap != NULL)
    {
        if(direction==0)    // heap是根节点
            printf("%2d is root\n", heap->key);
        else                // heap是分支节点
            printf("%2d is %2d's %6s child\n", heap->key, key, direction==1?"right" : "left");

        skewheap_print(heap->left, heap->key, -1);
        skewheap_print(heap->right,heap->key,  1);
    }
}

void print_skewheap(SkewHeap heap)
{
    if (heap != NULL)
        skewheap_print(heap, heap->key,  0);
}
