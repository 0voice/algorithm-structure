#include "binheap.h"
#include <stdio.h>

#define MaxSize (1000)

int main()
{
    PriorityQueue H;
    int i, j;

    H = Initialize(MaxSize);

    // 循环插入 MaxSize 个数字
    for (i = 0, j = MaxSize / 2; i < MaxSize; i++, j = (j + 71) % MaxSize)
        Insert(j, H);

    j = 0;

#if 0
    while (!IsEmpty(H))
    {
        int ele = DeleteMin(H);
        printf("%d ", ele);
    }
    printf("\n");
#endif


    while (!IsEmpty(H))
        if (DeleteMin(H) != j++)
            printf("Error in DeleteMin, %d\n", j);

    printf("Done...\n");
    return 0;
}
