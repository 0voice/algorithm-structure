/**
梅森数（Mersenne Prime）指的是形如2n-1的正整数，其中指数n是素数，即为Mn。如果一个梅森数是素数，则称其为梅森素数。例如22-1=3、23-1=7都是梅森素数。

当n=2，3，5，7时，Mn 都是素数，但n=11时，Mn=M11=211-1=2047=23X89，显然不是梅森素数。

1722年，瑞士数学大师欧拉证明了231-1=2147483647是一个素数，它共有10位数，成为当时世界上已知的最大素数。

迄今为止，人类仅发现了47个梅森素数。梅森素数历来都是数论研究中的一项重要内容，也是当今科学探索中的热点和难点问题。

试求出指数n<20的所有梅森素数。
*/

#include <math.h>
#include <stdio.h>
int prime(int n)
{
    int i;
    long k;
    k=sqrt(n)+1;
    for(i=2; i<=k; i++)
        if(n%i == 0)
            return 0;
    return 1;
}
int main()
{
    int mp, n=0, i;
    printf("Mersenne Prime:\n");
    for(i=2; i<=20; i++)
    {
        mp=pow(2,i)-1;
        if( prime(mp) )
        {
            n++;
            printf("M(%d)=%d", i, mp);
            printf("\n");
        }
    }
    printf("the number of Mersenne Prime less than 20 is:%d\n", n);
   
    return 0;
}


//运行结果：

//Mersenne Prime:
//M(2)=3
//M(3)=7
//M(5)=31
//M(7)=127
//M(13)=8191
//M(17)=131071
//M(19)=524287
//the number of Mersenne Prime less than 20 is:7
