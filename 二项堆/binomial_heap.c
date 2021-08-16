#include <stdio.h>
#include <stdlib.h>
#include "binomial_heap.h"

#define swap(a,b) (a^=b,b^=a,a^=b)

/*
 * 查找：在二项堆中查找键值为key的节点
 */
BinomialNode* binomial_search(BinomialHeap heap, Type key)
{
    BinomialNode *child;
    BinomialNode *parent = heap;

    parent = heap;
    while (parent != NULL)
    {
        if (parent->key == key)
            return parent;
        else
        {
            if((child = binomial_search(parent->child, key)) != NULL)
                return child;
            parent = parent->next;
        }
    }

    return NULL;
}

/*
 * 获取二项堆中的最小根节点(*y)
 *
 * 参数说明：
 *     heap    -- 二项堆
 *     prev_y  -- [输出参数]最小根节点y的前一个根节点
 *     y       -- [输出参数]最小根节点
 */
static void _binomial_minimum(BinomialHeap heap,
        BinomialNode **prev_y, BinomialNode **y)
{
    BinomialNode *x, *prev_x;    // x是用来遍历的当前节点

    if (heap==NULL)
        return ;

    prev_x  = heap;
    x       = heap->next;
    *prev_y = NULL;
    *y      = heap;
    // 找到最小节点
    while (x != NULL) {
        if (x->key < (*y)->key) {
            *y = x;
            *prev_y = prev_x;
        }
        prev_x = x;
        x = x->next;
    }
}

BinomialNode* binomial_minimum(BinomialHeap heap)
{
    BinomialNode *prev_y, *y;

    _binomial_minimum(heap, &prev_y, &y);

    return y;
}

/*
 * 合并两个二项堆：将child合并到heap中
 */
static void binomial_link(BinomialHeap child, BinomialHeap heap)
{
    child->parent = heap;
    child->next   = heap->child;
    heap->child = child;
    heap->degree++;
}

/*
 * 将h1, h2中的根表合并成一个按度数递增的链表，返回合并后的根节点
 */
static BinomialNode* binomial_merge(BinomialHeap h1, BinomialHeap h2)
{
    BinomialNode* head = NULL; //heap为指向新堆根结点
    BinomialNode** pos = &head;

    while (h1 && h2)
    {
        if (h1->degree < h2->degree)
        {
            *pos = h1;
            h1 = h1->next;
        }
        else
        {
            *pos = h2;
            h2 = h2->next;
        }
        pos = &(*pos)->next;
    }
    if (h1)
        *pos = h1;
    else
        *pos = h2;

    return head;
}

/*
 * 合并二项堆：将h1, h2合并成一个堆，并返回合并后的堆
 */
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2)
{
    BinomialNode *heap;
    BinomialNode *prev_x, *x, *next_x;

    // 将h1, h2中的根表合并成一个按度数递增的链表heap
    heap = binomial_merge(h1, h2);
    if (heap == NULL)
        return NULL;

    prev_x = NULL;
    x      = heap;
    next_x = x->next;

    while (next_x != NULL)
    {
        if (   (x->degree != next_x->degree)
            || ((next_x->next != NULL) && (next_x->degree == next_x->next->degree)))
        {
            // Case 1: x->degree != next_x->degree
            // Case 2: x->degree == next_x->degree == next_x->next->degree
            prev_x = x;
            x = next_x;
        }
        else if (x->key <= next_x->key)
        {
            // Case 3: x->degree == next_x->degree != next_x->next->degree
            //      && x->key    <= next_x->key
            x->next = next_x->next;
            binomial_link(next_x, x);
        }
        else
        {
            // Case 4: x->degree == next_x->degree != next_x->next->degree
            //      && x->key    >  next_x->key
            if (prev_x == NULL)
            {
                heap = next_x;
            }
            else
            {
                prev_x->next = next_x;
            }
            binomial_link(x, next_x);
            x = next_x;
        }
        next_x = x->next;
    }

    return heap;
}

/*
 * 新建二项堆节点
 */
static BinomialNode* make_binomial_node(Type key)
{
    BinomialNode* node;

    node = (BinomialNode*)malloc(sizeof(BinomialNode));
    if (node==NULL)
    {
        printf("malloc BinomialNode failed!\n");
        return NULL;
    }

    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->next = NULL;

    return node;
}

/*
 * 新建key对应的节点，并将其插入到二项堆中。
 *
 * 参数说明：
 *     heap -- 原始的二项树。
 *     key -- 键值
 * 返回值：
 *     插入key之后的二项树
 */
BinomialNode* binomial_insert(BinomialHeap heap, Type key)
{
    BinomialNode* node;

    if (binomial_search(heap, key) != NULL)
    {
        printf("insert failed: the key(%d) is existed already!\n", key);
        return heap;
    }

    node = make_binomial_node(key);
    if (node==NULL)
        return heap;

    return binomial_union(heap, node);
}

/*
 * 反转二项堆heap
 */
static BinomialNode* binomial_reverse(BinomialNode* heap)
{
    BinomialNode* next;
    BinomialNode* tail = NULL;

    if (!heap)
        return heap;

    heap->parent = NULL;
    while (heap->next)
    {
        next          = heap->next;
        heap->next = tail;
        tail          = heap;
        heap          = next;
        heap->parent  = NULL;
    }
    heap->next = tail;

    return heap;
}

/*
 * 移除最小节点，并返回移除节点后的二项堆
 */
BinomialNode* binomial_extract_minimum(BinomialHeap heap)
{
    BinomialNode *y, *prev_y;    // y是最小节点

    if (heap==NULL)
        return heap;

    // 找到"最小节点根y"和"它的前一个根节点prev_y"
    _binomial_minimum(heap, &prev_y, &y);

    if (prev_y == NULL)    // heap的根节点就是最小根节点
        heap = heap->next;
    else                // heap的根节点不是最小根节点
        prev_y->next = y->next;

    // 反转最小节点的左孩子，得到最小堆child；
    // 这样，就使得最小节点所在二项树的孩子们都脱离出来成为一棵独立的二项树(不包括最小节点)
    BinomialNode* child = binomial_reverse(y->child);
    // 将"删除最小节点的二项堆child"和"heap"进行合并。
    heap = binomial_union(heap, child);

    // 删除最小节点
    free(y);

    return heap;
}

/*
 * 减少关键字的值：将二项堆heap中的节点node的键值减小为key。
 */
static void binomial_decrease_key(BinomialHeap heap, BinomialNode *node, Type key)
{
    if ((key >= node->key) || (binomial_search(heap, key) != NULL))
    {
        printf("decrease failed: the new key(%d) is existed already, \
                or is no smaller than current key(%d)\n", key, node->key);
        return ;
    }
    node->key = key;

    BinomialNode *child, *parent;
    child = node;
    parent = node->parent;
    while(parent != NULL && child->key < parent->key)
    {
        swap(parent->key, child->key);
        child = parent;
        parent = child->parent;
    }
}

/*
 * 增加关键字的值：将二项堆heap中的节点node的键值增加为key。
 */
static void binomial_increase_key(BinomialHeap heap, BinomialNode *node, Type key)
{
    if ((key <= node->key) || (binomial_search(heap, key) != NULL))
    {
        printf("increase failed: the new key(%d) is existed already, \
                or is no greater than current key(%d)\n", key, node->key);
        return ;
    }
    node->key = key;

    BinomialNode *cur, *child, *least;
    cur = node;
    child = cur->child;
    while (child != NULL)
    {
        if(cur->key > child->key)
        {
            // 如果"当前节点" < "它的左孩子"，
            // 则在"它的孩子中(左孩子 和 左孩子的兄弟)"中，找出最小的节点；
            // 然后将"最小节点的值" 和 "当前节点的值"进行互换
            least = child;
            while(child->next != NULL)
            {
                if (least->key > child->next->key)
                {
                    least = child->next;
                }
                child = child->next;
            }
            // 交换最小节点和当前节点的值
            swap(least->key, cur->key);

            // 交换数据之后，再对"原最小节点"进行调整，使它满足最小堆的性质：父节点 <= 子节点
            cur = least;
            child = cur->child;
        }
        else
        {
            child = child->next;
        }
    }
}

/*
 * 更新二项堆heap的节点node的键值为key
 */
static void binomial_update_key(BinomialHeap heap, BinomialNode* node, Type key)
{
    if (node == NULL)
        return ;

    if(key < node->key)
        binomial_decrease_key(heap, node, key);
    else if(key > node->key)
        binomial_increase_key(heap, node, key);
    else
        printf("No need to update!!!\n");
}

/*
 * 将二项堆heap的键值oldkey更新为newkey
 */
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey)
{
    BinomialNode *node;

    node = binomial_search(heap, oldkey);
    if (node != NULL)
        binomial_update_key(heap, node, newkey);
}

/*
 * 删除节点：删除键值为key的节点，并返回删除节点后的二项树
 */
BinomialNode* binomial_delete(BinomialHeap heap, Type key)
{
    BinomialNode *node;
    BinomialNode *parent, *prev, *pos;

    if (heap==NULL)
        return heap;

    // 查找键值为key的节点
    if ((node = binomial_search(heap, key)) == NULL)
        return heap;

    // 将被删除的节点的数据数据上移到它所在的二项树的根节点
    parent = node->parent;
    while (parent != NULL)
    {
        // 交换数据
        swap(node->key, parent->key);
        // 下一个父节点
        node   = parent;
        parent = node->parent;
    }

    // 找到node的前一个根节点(prev)
    prev = NULL;
    pos  = heap;
    while (pos != node)
    {
        prev = pos;
        pos  = pos->next;
    }
    // 移除node节点
    if (prev)
        prev->next = node->next;
    else
        heap = node->next;

    heap = binomial_union(heap, binomial_reverse(node->child));

    free(node);

    return heap;
}

/*
 * 打印"二项堆"
 *
 * 参数说明：
 *     node       -- 当前节点
 *     prev       -- 当前节点的前一个节点(父节点or兄弟节点)
 *     direction  --  1，表示当前节点是一个左孩子;
 *                    2，表示当前节点是一个兄弟节点。
 */
static void _binomial_print(BinomialNode *node, BinomialNode *prev, int direction)
{
    while(node != NULL)
    {
        //printf("%2d \n", node->key);
        if (direction == 1)
            printf("\t%2d(%d) is %2d's child\n", node->key, node->degree, prev->key);
        else
            printf("\t%2d(%d) is %2d's next\n", node->key, node->degree, prev->key);

        if (node->child != NULL)
            _binomial_print(node->child, node, 1);

        // 兄弟节点
        prev = node;
        node = node->next;
        direction = 2;
    }
}

void binomial_print(BinomialHeap heap)
{
    if (heap == NULL)
        return ;

    BinomialNode *p = heap;
    printf("== 二项堆( ");
    while (p != NULL)
    {
        printf("B%d ", p->degree);
        p = p->next;
    }
    printf(")的详细信息：\n");

    int i=0;
    while (heap != NULL)
    {
        i++;
        printf("%d. 二项树B%d: \n", i, heap->degree);
        printf("\t%2d(%d) is root\n", heap->key, heap->degree);

        _binomial_print(heap->child, heap, 1);
        heap = heap->next;
    }
    printf("\n");
}
