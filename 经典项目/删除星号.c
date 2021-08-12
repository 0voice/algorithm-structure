#include <stdio.h>
int fun(char *a, char *h, char *p)
{
    int i, j;
    /*删除指针h与p之间的所有“*”*/
    for(i=0,j=0; &h[i]<p; i++)
        if(h[i]!='*')
            h[j++]=h[i];
    /*将指针p至字符串尾部的所有字符前移*/
    for(i=0; p[i]; i++,j++)
        h[j]=p[i];
    h[j]='\0';  /*在字符串尾部添加结束标志*/
    return 0;
}
int main( )
{
    char s[81], *t, *f;
    printf("Enter a string :\n");
    gets(s);  /*输入字符串*/
    t=f=s;  /*用字符指针t、f指向串s*/
   
    while(*t)
        t++;
    t--;  /*将指针t定位到字符串中最后一个字符*/
    while(*t == '*')  /*指针t指向字符串中最后一个字符*/
        t--;
    while (*f == '*')  /*指针f指向字符串中第一个字符*/
        f++;
    fun(s, f, t);
    printf("The string after deleted:\n");  /*输出结果*/
    puts(s);
    return 0;
}

//运行结果：
//Enter a string :
//****A*BC*DEF*G********
//The string after deleted:
//****ABCDEFG********
