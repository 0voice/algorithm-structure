#include <stdio.h>
#include "skewheap.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
    int i;
    int a[]= {10,40,24,30,36,20,12,16};
    int b[]= {17,13,11,15,19,21,23};
    int alen=LENGTH(a);
    int blen=LENGTH(b);
    SkewHeap ha,hb;

    ha=hb=NULL;

    printf("== 斜堆(ha)中依次添加: ");
    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        ha = insert_skewheap(ha, a[i]);
    }
    printf("\n== 斜堆(ha)的详细信息: \n");
    print_skewheap(ha);


    printf("\n== 斜堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = insert_skewheap(hb, b[i]);
    }
    printf("\n== 斜堆(hb)的详细信息: \n");
    print_skewheap(hb);

    // 将"斜堆hb"合并到"斜堆ha"中。
    ha = merge_skewheap(ha, hb);
    printf("\n== 合并ha和hb后的详细信息: \n");
    print_skewheap(ha);


    // 销毁斜堆
    destroy_skewheap(ha);
}
