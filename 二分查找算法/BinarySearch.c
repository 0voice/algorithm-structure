

// 实现二分查找
#include <stdio.h>
#include <stdlib.h>

void BinarySearch(int *arr, int start, int end, int num);

int main(int argc, const char * argv[])
{
    int array[] = {4,5,6,7,8,9};

    BinarySearch(array, 0, 5, 99);

    return 0;
}

void BinarySearch(int *arr, int start, int end, int num)
{
    int mid = (start + end) / 2;
    if (arr[mid] == num)
    {
        printf("%d ",mid);
        return ;
    }

    if (start == end)
    {
        printf("没有找到");
        return ;
    }

    if (num < arr[mid])
    {
        BinarySearch(arr, start, mid, num);
    }

    if (num > arr[mid])
    {
        BinarySearch(arr, mid + 1, end, num);
    }

    return ;
}