//自定义一个函数，将字符串转换为整数，原型为：
//
//int ascii_to_integer( char *string );
//
//这个字符串参数必须包含一个或多个数字，函数应该把这些数字字符转换为整数并返回这个整数。如果字符串参数包含了任何非数字字符，函数就返回零。请不必担心算术溢出。
//提示：这个技巧很简单你每发现一个数字，把当前值乘以10，并把这个值和新数字所代表的值相加。
//这个问题应该用迭代方法解决，而不应采用递归方法。


#include <stdio.h>

// 把一个数字字符串转换为一个整数。
int ascii_to_integer( char *string )
{
    int value; value = 0;

    // 逐个把字符串的字符转换为数字。
    while( *string >= '0' && *string <= '9' ){
        value *= 10;
        value += *string - '0';
        string++;
    }

    //错误检查：如杲由于遇到一个非数字字符而终止，把结果设置为0
    if( *string != '\0' )
        value = 0;
    return value;
}

int main()
{
    char* numChar = "102";
    printf("%d\n", ascii_to_integer(numChar)+3);
    
    return 0;
}

