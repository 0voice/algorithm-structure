//求13的13次方的最后三位数。

#include <stdio.h>
int main()
{
    int i, x, y, last=1;  /*变量last保存求得的x的y次方的部分积的后三位*/
    printf("Input x and y:\n");
    scanf("%d %d", &x, &y);
    for(i=1; i<=y; i++)  /*x自乘的次数y*/
        last = last * x % 1000;  /*将last乘x后对1000取模，即求积的后三位*/
    printf("The last three digits is:%d\n", last);
   
    return 0;
}

//运行结果：

//Input x and y:
//13 13
//The last three digits is:253
