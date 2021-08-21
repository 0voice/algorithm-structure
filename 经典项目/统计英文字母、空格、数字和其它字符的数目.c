#include <stdio.h>

int main(){
    char c;  //用户输入的字符 
    int letters=0,  // 字母数目 
        space=0,  // 空格数目 
        digit=0,  // 整数数目 
        others=0;  // 其他字符数目

    printf("输入一些字符：");
    while((c=getchar())!='\n'){  // 每次读取一个字符，回车时结束
        if(c>='a'&&c<='z'||c>='A'&&c<='Z')
            letters++;
        else if(c==' ')
            space++;
        else if(c>='0'&&c<='9')
            digit++;
        else
            others++;
    }
    
    printf("\n统计结果:\n英文字母=%d\n空格=%d\n整数=%d\n其他字符=%d\n\n", letters, space, digit, others);

    return 0;
}


//运行结果：

//输入一些字符：rwrwewre2345asdJSJQI%^&(&   *&sdf YY( 2342-k'

//统计结果:
//英文字母=22
//空格=5
//整数=8
//其他字符=10
