/**
请编写程序，实现以下功能：在字符串中的所有数字字符前加一个$字符。例如，输入 A1B23CD45，输出 A$1B$2$3CD$4$5。
*/

#include <stdio.h>
int fun(char *s)
{
    char t[80];
    int i, j;
    for(i=0; s[i]; i++)  /*将串s拷贝至串t*/
        t[i]=s[i];
    t[i]='\0';
    for(i=0,j=0; t[i]; i++)
    /*对于数字字符先写一个$符号，再写该数字字符*/
        if(t[i]>='0' && t[i]<='9')
        {
            s[j++]='$';
            s[j++]=t[i];
        }
    /*对于非数字字符原样写入串s*/
        else
            s[j++]=t[i];
    s[j]='\0';  /*在串s结尾加结束标志*/
    return 0;
}
int main()
{
    char s[80];
    printf ( "Enter a string:" );
    scanf ("%s", s);  /*输入字符串*/
    fun(s);
    printf ("The result: %s\n", s);  /*输出结果*/
    return 0;
}

//运行结果：

//Enter a string:A1B23CD45
//The result: A$1B$2$3CD$4$5
