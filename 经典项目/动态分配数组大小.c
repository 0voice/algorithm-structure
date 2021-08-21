//我们知道，C语言中的数组大小是固定的，定义的时候必须要给一个常量值，不能是变量。

//这带来了很大的不便，如果数组过小，不能容下所有数组，如果过大，浪费资源。

//下面的代码实现了简单的动态数组：

#include <stdio.h>
#include <stdlib.h>

int main()
{
    //从控制台获取初始数组大小
    int N;
    int *a;
    int i;

    printf("Input array length:");
    scanf("%d\n",&N);

    //分配空间
    a=(int *)calloc(N,sizeof(int));
    //填充数据
    for(i=0;i<N;i++){
        a[i]=i+1;
        printf("%-5d",a[i]);
        if((i+1)%10==0){
            printf("\n");
        }
    }
    //释放内存
    free(a);
    a=NULL;

    printf("\n");
    return 0;
}


//运行结果：
//Input array length:20

//1    2    3    4    5    6    7    8    9    10
//11   12   13   14   15   16   17   18   19   20
