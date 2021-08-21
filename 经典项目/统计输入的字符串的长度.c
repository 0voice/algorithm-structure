#include <stdio.h>
#include <string.h>

int main(){
   char str[21];
   int strLen;
   
   printf("Input your string: ");
   scanf("%s", str);
   strLen = strlen(str);
       printf("string = %s\nlength = %d\n", str, strLen);
   
   return 0;
}


//运行结果：

//Input your string: 1234567890
//string = 1234567890
//length = 10
//----------------------------------
//Input your string: 123456 7890
//string = 123456
//length = 6
//----------------------------------
//Input your string: 1234567890123456789012345
//string = 1234567890123456789012345
//length = 25
// 提示程序停止运行
