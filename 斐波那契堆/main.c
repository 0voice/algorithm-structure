#include <stdio.h>
#include "fibonacci_heap.h"

#define DEBUG 0

#if DEBUG
#define log(x, ...)   printf(x, __VA_ARGS__)
#else
#define log(x, ...)   
#endif

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

// 共8个
int a[] = {12,  7, 25, 15, 28, 
           33, 41, 1};
// 共14个
int b[] = {18, 35, 20, 42,  9, 
           31, 23,  6, 48, 11, 
           24, 52, 13, 2};

// 验证"基本信息(斐波那契堆的结构)"
void test_basic()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 斐波那契堆hb
    printf("== 斐波那契堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(hb)删除最小节点\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    fib_heap_destroy(hb);
}

// 验证"插入操作"
void test_insert()
{
    int i;
    int alen=LENGTH(a);
    FibHeap *ha = fib_heap_make();

    // 斐波那契堆ha
    printf("== 斐波那契堆(ha)中依次添加: ");

    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        fib_heap_insert_key(ha, a[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(ha)删除最小节点\n");
    fib_heap_extract_min(ha);
    fib_print(ha);

    // 插入50
    printf("== 插入50\n");
    fib_heap_insert_key(ha, 50);
    fib_print(ha);

    fib_heap_destroy(ha);
}

// 验证"合并操作"
void test_union()
{
    int i;
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    FibHeap *ha = fib_heap_make();
    FibHeap *hb = fib_heap_make();

    // 斐波那契堆ha
    printf("== 斐波那契堆(ha)中依次添加: ");

    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        fib_heap_insert_key(ha, a[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(ha)删除最小节点\n");
    fib_heap_extract_min(ha);
    fib_print(ha);

    // 斐波那契堆hb
    printf("== 斐波那契堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(hb)删除最小节点\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    // 将"斐波那契堆hb"合并到"斐波那契堆ha"中。
    printf("== 合并ha和hb\n");
    ha = fib_heap_union(ha, hb);
    fib_print(ha);

    // 销毁堆
    fib_heap_destroy(ha);
}

// 验证"删除最小节点"
void test_remove_min()
{
    int i;
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    FibHeap *ha = fib_heap_make();
    FibHeap *hb = fib_heap_make();

    // 斐波那契堆ha
    printf("== 斐波那契堆(ha)中依次添加: ");

    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        fib_heap_insert_key(ha, a[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(ha)删除最小节点\n");
    fib_heap_extract_min(ha);
    //fib_print(ha);

    // 斐波那契堆hb
    printf("== 斐波那契堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(hb)删除最小节点\n");
    fib_heap_extract_min(hb);
    //fib_print(hb);

    // 将"斐波那契堆hb"合并到"斐波那契堆ha"中。
    printf("== 合并ha和hb\n");
    ha = fib_heap_union(ha, hb);
    fib_print(ha);

    printf("== 删除最小节点\n");
    fib_heap_extract_min(ha);
    fib_print(ha);

    // 销毁堆
    fib_heap_destroy(ha);
}

// 验证"减小节点"
void test_decrease()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 斐波那契堆hb
    printf("== 斐波那契堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(hb)删除最小节点\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    printf("== 将20减小为2\n");
    fib_heap_update(hb, 20, 2);
    fib_print(hb);

    fib_heap_destroy(hb);
}

// 验证"增大节点"
void test_increase()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 斐波那契堆hb
    printf("== 斐波那契堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(hb)删除最小节点\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    fib_heap_update(hb, 20, 60);
    printf("== 将20增加为60\n");
    fib_print(hb);

    fib_heap_destroy(hb);
}

// 验证"删除节点"
void test_delete()
{
    int i;
    int blen=LENGTH(b);
    FibHeap *hb = fib_heap_make();

    // 斐波那契堆hb
    printf("== 斐波那契堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        fib_heap_insert_key(hb, b[i]);
    }
    printf("\n");
    printf("== 斐波那契堆(hb)删除最小节点\n");
    fib_heap_extract_min(hb);
    fib_print(hb);

    fib_heap_delete(hb, 20);
    printf("== 删除节点20\n");
    fib_print(hb);

    fib_heap_destroy(hb);
}

void main()
{
    // 验证"基本信息(斐波那契堆的结构)"
    test_basic();
    // 验证"插入操作"
    //test_insert();
    // 验证"合并操作"
    //test_union();
    // 验证"删除最小节点"
    //test_remove_min();
    // 验证"减小节点"
    //test_decrease();
    // 验证"增大节点"
    //test_increase();
    // 验证"删除节点"
    //test_delete();
}
