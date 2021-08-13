//给定一个 M 进制的数 x，实现对 x 向任意的一个非 M 进制的数的转换。

#include <stdio.h>

#define MAXCHAR 101  /*最大允许字符串长度*/

int char_to_num(char ch);  /*返回字符对应的数字*/ 
char num_to_char(int num);  /*返回数字对应的字符*/
long source_to_decimal(char temp[], int source);  /*返回由原数转换成的10进制数*/
int decimal_to_object(char temp[], long decimal_num, int object);  /*返回转换成目标数制后字符数组的长度*/
void output(char temp[], int length);  /*将字符数组逆序打印*/

int main()
{
    int source;  /*存储原数制*/
    int object;   /*存储目标数制*/
    int length;  /*存储转换成目标数制后字符数组的长度*/
    long decimal_num;  /*存储转换成的10进制数*/
    char temp[MAXCHAR];   /*存储待转换的数值和转换后的数值*/
    int flag = 1;  /*存储是否退出程序的标志*/
    while(flag)  /*利用输入的flag值控制循环是否结束*/
    {
        printf("转换前的数是：");
        scanf("%s", temp);
        printf("转换前的数制是：");
        scanf("%d", &source);
        printf("转换后的数制是：");
        scanf("%d", &object);
        printf("转换后的数是：");
        decimal_num = source_to_decimal(temp, source);
        length = decimal_to_object(temp, decimal_num, object);
        output(temp, length);
        printf("继续请输入1,否则输入0：\n");
        scanf("%d", &flag);
    }

    return 0;
}
/*将字符转换成数字*/
int char_to_num(char ch)
{
    if(ch>='0' && ch<='9')
        return ch-'0';  /*将数字字符转换成数字*/
    else
        return ch-'A'+10;  /*将字母字符转换成数字*/
}
char num_to_char(int num)
{
    if(num>=0 && num<=9)
        return (char)('0'+num-0);  /*将0~9之间的数字转换成字符*/
    else
        return (char)('A'+num-10);  /*将大于10的数字转换成字符*/
}
long source_to_decimal(char temp[], int source)
{
    long decimal_num = 0;  /*存储展开之后的和*/
    int length;
    int i;
    for( i=0; temp[i]!='\0'; i++ );
    length=i;
    for( i=0; i<=length-1; i++ )  /*累加*/
        decimal_num = (decimal_num*source) + char_to_num(temp[i]);
    return decimal_num;
}
int decimal_to_object(char temp[], long decimal_num, int object)
{
    int i=0;
    while(decimal_num)
    {
        temp[i] = num_to_char(decimal_num % object);  /*求出余数并转换为字符*/
        decimal_num = decimal_num / object;  /*用十进制数除以基数*/
        i++;
    }
    temp[i]='\0';
    return i;
}
void output(char temp[], int length)
{
    int i;
    for( i=length-1; i>=0; i--)  /*输出temp数组中的值*/
        printf("%c", temp[i]);
    printf("\n");
}

/**
运行结果：
转换前的数是：123
转换前的数制是：10
转换后的数制是：2
转换后的数是：1111011
继续请输入1,否则输入0：
1
转换前的数是：123
转换前的数制是：10
转换后的数制是：8
转换后的数是：173
继续请输入1,否则输入0：
1
转换前的数是：123
转换前的数制是：10
转换后的数制是：16
转换后的数是：7B
继续请输入1,否则输入0：
1
转换前的数是：12121
转换前的数制是：8
转换后的数制是：16
转换后的数是：1451
继续请输入1,否则输入0：
*/
