//打印所有不超过n（取n<256）的其平方具有对称性质的数（也称回文数）。


#include<stdio.h>
int main()
{
    int m[16], n, i, t, count=0;
    long unsigned a, k;
    printf("No.    number     it's square(palindrome)\n");
    for( n=1; n<256; n++ )  /*穷举n的取值范围*/
    {
        k=0; t=1; a=n*n;  /*计算n的平方*/
        for( i=0; a!=0; i++ )  /*从低到高分解数a的每一位存于数组m[1]~m[16]*/
        {
            m[i] = a % 10;
            a /= 10;
        }
        for(; i>0; i--)
        {
            k += m[i-1] * t;  /*t记录某一位置对应的权值 */
            t *= 10;
        }
        if(k == n*n)
            printf("%2d%10d%10d\n", ++count, n, n*n);
    }
    return 0;
}

//运行结果：

//No.    number     it's square(palindrome)
 //1         1         1
 //2         2         4
 //3         3         9
 //4        11       121
 //5        22       484
 //6        26       676
 //7       101     10201
 //8       111     12321
 //9       121     14641
//10       202     40804
//11       212     44944
