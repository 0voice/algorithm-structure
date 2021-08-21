//下面的程序将从字符数组中删除特定的字符，要求字符数组和要删除的字符都是手动输入。
//主要涉及知识点：字符数组的输入输出，及相应的处理。

#include <stdio.h>
int main(){
    char s[80], c;
    int j, k;
    printf("Enter a string: ");
    gets(s);
    printf("Enter a character: ");
    c=getchar( );
    for(j=k=0; s[j]!='\0'; j++)
        if(s[j]!=c)
            s[k++]=s[j];
    s[k]= '\0';
    printf("\n%s",s);

    return 0;
}

//运行结果：
//Enter a string: www.0voice.com
//Enter a character:i
//The final string is: www.0voce.com
