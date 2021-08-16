/**
 * C语言实现的左倾堆
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <stdio.h>
#include <stdlib.h>
#include "leftist.h"

/*
 * 前序遍历"左倾堆"
 */
void preorder_leftist(LeftistHeap heap)
{
    if(heap != NULL)
    {
        printf("%d ", heap->key);
        preorder_leftist(heap->left);
        preorder_leftist(heap->right);
    }
}

/*
 * 中序遍历"左倾堆"
 */
void inorder_leftist(LeftistHeap heap)
{
    if(heap != NULL)
    {
        inorder_leftist(heap->left);
        printf("%d ", heap->key);
        inorder_leftist(heap->right);
    }
}

/*
 * 后序遍历"左倾堆"
 */
void postorder_leftist(LeftistHeap heap)
{
    if(heap != NULL)
    {
        postorder_leftist(heap->left);
        postorder_leftist(heap->right);
        printf("%d ", heap->key);
    }
}

/*
 * 交换两个节点的内容
 */
static void swap_leftist_node(LeftistNode *x, LeftistNode *y)
{
    LeftistNode tmp = *x;
    *x = *y;
    *y = tmp;
}

/*
 * 获取最小值
 *
 * 返回值：
 *    成功返回0，失败返回-1
 */
int leftist_minimum(LeftistHeap heap, int *pval)
{
    if (heap == NULL)
        return -1;

    *pval = heap->key;

    return 0;
}

/*
 * 合并"左倾堆x"和"左倾堆y"
 *
 * 返回值：
 *     合并得到的树的根节点
 */
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;

    // 合并x和y时，将x作为合并后的树的根；
    // 这里的操作是保证: x的key < y的key
    if(x->key > y->key)
        swap_leftist_node(x, y);

    // 将x的右孩子和y合并，"合并后的树的根"是x的右孩子。
    x->right = merge_leftist(x->right, y);

    // 如果"x的左孩子为空" 或者 "x的左孩子的npl<右孩子的npl"
    // 则，交换x和y
    if(x->left == NULL || x->left->npl < x->right->npl)
    {
        LeftistNode *tmp = x->left;
        x->left = x->right;
        x->right = tmp;
    }
    // 设置合并后的新树(x)的npl
    if (x->right == NULL || x->left == NULL)
        x->npl = 0;
    else
        x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

    return x;
}

/*
 * 新建结点(key)，并将其插入到左倾堆中
 *
 * 参数说明：
 *     heap 左倾堆的根结点
 *     key 插入结点的键值
 * 返回值：
 *     根节点
 */
LeftistNode* insert_leftist(LeftistHeap heap, Type key)
{
    LeftistNode *node;    // 新建结点

    // 如果新建结点失败，则返回。
    if ((node = (LeftistNode *)malloc(sizeof(LeftistNode))) == NULL)
        return heap;
    node->key = key;
    node->npl = 0;
    node->left = node->right = NULL;

    return merge_leftist(heap, node);
}

/*
 * 取出根节点
 *
 * 返回值：
 *     取出根节点后的新树的根节点
 */
LeftistNode* delete_leftist(LeftistHeap heap)
{
    if (heap == NULL)
        return NULL;

    LeftistNode *l = heap->left;
    LeftistNode *r = heap->right;

    // 删除根节点
    free(heap);

    return merge_leftist(l, r); // 返回左右子树合并后的新树
}

/*
 * 销毁左倾堆
 */
void destroy_leftist(LeftistHeap heap)
{
    if (heap==NULL)
        return ;

    if (heap->left != NULL)
        destroy_leftist(heap->left);
    if (heap->right != NULL)
        destroy_leftist(heap->right);

    free(heap);
}

/*
 * 打印"左倾堆"
 *
 * heap       -- 左倾堆的节点
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
static void leftist_print(LeftistHeap heap, Type key, int direction)
{
    if(heap != NULL)
    {
        if(direction==0)    // heap是根节点
            printf("%2d(%d) is root\n", heap->key, heap->npl);
        else                // heap是分支节点
            printf("%2d(%d) is %2d's %6s child\n", heap->key, heap->npl, key, direction==1?"right" : "left");

        leftist_print(heap->left, heap->key, -1);
        leftist_print(heap->right,heap->key,  1);
    }
}

void print_leftist(LeftistHeap heap)
{
    if (heap != NULL)
        leftist_print(heap, heap->key,  0);
}
