#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_

typedef int Type;

typedef struct _FibonacciNode
{
    Type   key;                        // 关键字(键值)
    int degree;                        // 度数
    struct _FibonacciNode *left;    // 左兄弟
    struct _FibonacciNode *right;    // 右兄弟
    struct _FibonacciNode *child;    // 第一个孩子节点
    struct _FibonacciNode *parent;    // 父节点
    int marked;                       //是否被删除第1个孩子(1表示删除，0表示未删除)
}FibonacciNode, FibNode;

typedef struct _FibonacciHeap{
    int   keyNum;                    // 堆中节点的总数
    int   maxDegree;                // 最大度
    struct _FibonacciNode *min;        // 最小节点(某个最小堆的根节点)
    struct _FibonacciNode **cons;    // 最大度的内存区域
}FibonacciHeap, FibHeap;

// 创建Fibonacci堆
FibHeap* fib_heap_make();
// 新建键值为key的节点，并将其插入到斐波那契堆中
void fib_heap_insert_key(FibHeap *heap, Type key);
// 删除键值为key的结点
void fib_heap_delete(FibHeap *heap, Type key);
// 移除最小节点
void fib_heap_extract_min(FibHeap *heap);
// 更新heap的中的oldkey为newkey
void fib_heap_update(FibHeap *heap, Type oldkey, Type newkey);
// 将h1, h2合并成一个堆，并返回合并后的堆
FibHeap* fib_heap_union(FibHeap *h1, FibHeap *h2);
// 在斐波那契堆heap中是否存在键值为key的节点；存在返回1，否则返回0。
int fib_heap_contains(FibHeap *heap, Type key);
// 获取最小节点对应的值(保存在pkey中)；成功返回1，失败返回0。
int fib_heap_get_min(FibHeap *heap, Type *pkey);
// 销毁斐波那契堆
void fib_heap_destroy(FibHeap *heap);
// 打印"斐波那契堆"
void fib_print(FibHeap *heap);

#endif
