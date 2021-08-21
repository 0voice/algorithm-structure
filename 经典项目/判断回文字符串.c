//输入一个字符串，判断其是否为回文。
//所谓回文字符串，是指从左到右读和从右到左读完全相同的字符串。
//主要涉及知识点：字符数组的输入输出，及相应的处理。
//这个问题，可以从字符串的两头开始比较，即第1个字符和倒数第1个字符比较，第2个字符和倒数第2个字符比较，以此类推...如果出现字符不相等的情况，说明不是回文，如果全部相等，说明是回文。


#include <stdio.h>
#include <string.h>
#include <string.h>
void main(){
    char s[100];  // 存放输入的字符串 
    int i, j, n;
    printf("输入字符串：");
    gets(s);
    
    n=strlen(s);
    for(i=0,j=n-1;i<j;i++,j--)
        if(s[i]!=s[j]) break;
        if(i>=j)
            printf("是回文串\n");
        else
            printf("不是回文串\n");
}

//运行结果：

//输入字符串：abcdcba
//是回文串
