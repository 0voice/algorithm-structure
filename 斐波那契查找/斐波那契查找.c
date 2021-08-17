#include <stdio.h>

#define FIB_MAXSIZE 100

/**
 * 生成斐波那契数列
 * @param fib：指向存储斐波那契数列的数组的指针
 * @param size：斐波那契数列长度
 */
void ProduceFib(int *fib, int size)
{
    int i;

    fib[0] = 1;
    fib[1] = 1;

    for (i = 2; i < size; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

/**
 * 斐波那契查找，查找成功返回位序，否则返回-1
 * @param data：有序表数组
 * @param length：有序表元素个数
 * @param searchValue：待查找关键字
 */
int FibonacciSearch(int *data, int length, int searchValue)
{
    int low, high, mid, k, i, fib[FIB_MAXSIZE];

    low = 0;
    high = length - 1;

    ProduceFib(fib, FIB_MAXSIZE);

    k = 0;
    // 找到有序表元素个数在斐波那契数列中最接近的最大数列值
    while (high > fib[k] - 1)
    {
        k++;
    }

    // 补齐有序表
    for (i = length; i <= fib[k] - 1; i++)
    {
        data[i] = data[high];
    }

    while (low <= high)
    {
        mid = low + fib[k - 1] - 1;   // 根据斐波那契数列进行黄金分割

        if (data[mid] == searchValue)
        {
            if (mid <= length - 1)
            {
                return mid;
            }
            else
            {
                // 说明查找得到的数据元素是补全值
                return length - 1;
            }
        }

        if (data[mid] > searchValue)
        {
            high = mid - 1;
            k = k - 1;
        }

        if (data[mid] < searchValue)
        {
            low = mid + 1;
            k = k - 2;
        }
    }

    return -1;
}

int main()
{
    int data[] = {1,3,5,7,9,11,13,15,17,19,21};

    int index = FibonacciSearch(data, 11, 19);
    printf("%d\n", index);

    return 0;
}
