#include <stdio.h>

/**
 * 计算 Hermite polynomial 的值
 *
 * 输入：
 *    n, x：用于标识值
 *
 * 输出：
 *    polynomial的值（返回值）
**/

int hermite( int n, int x )
{
    // 处理不需要递归的特殊情况。
    if( n <= 0 )
        return 1;
    if( n == 1 )
        return 2 * x;

    // 否则，递归地计算结果值。
    return 2 * x * hermite( n - l, x ) - 2 * ( n - 1 ) * hermite ( n - 2, x );
}

int main()
{
    printf("%d\n", hermite(3,2));
    
    return 0;
}
