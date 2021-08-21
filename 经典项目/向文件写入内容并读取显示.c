//将学生信息（姓名、年龄、学号和平均分）写入文件，然后读取显示出来。

//要求：
//从控制台输入学生信息；
//可以输入任意数目的学生信息；
//文件每行存储一条学生信息，姓名、年龄、学号、平均分以tab(\t)为分隔。

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define FILE_PATH "D:/demo.txt"  // 文件路径

int main(){
    char name[20];  // 姓名 
    int age;  // 年龄 
    int studNo;  // 学号 
    float score;  // 平均分 
    FILE *fp;  // 文件指针 
    
    // 判断文件是否能够正确创建/打开 
    if( (fp=fopen(FILE_PATH,"wt+")) == NULL ){
        perror(FILE_PATH);
        exit(1);
    }
    
    // 从控制台输入学生信息并写入文件
    printf("请输入姓名、年龄、学号和平均分(以空格分隔)：\n");
    while(scanf("%s %d %d %f", name, &age, &studNo, &score)!= EOF){
        fprintf(fp,"%s\t%d\t%d\t%f\n", name, age, studNo, score);
    }
    // 刷新缓冲区，将缓冲区的内容写入文件 
    fflush(fp);
    // 重置文件内部位置指针，让位置指针指向文件开头
    rewind(fp);

    // 从文件中读取学生信息
    printf("\n读取文件内容：\n");
    while(fscanf(fp, "%s\t%d\t%d\t%f", name, &age, &studNo, &score) != EOF){
        printf("%s  %d  %d  %f\n", name, age, studNo, score);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}


//运行结果：

//请输入姓名、年龄、学号和平均分(以空格分隔)：
//棍哥 25 1 99.99
//码农宿舍 2 3 89.9
//www.0voice.com 3 2 100
//^Z  // ^Z 为 Ctrl+Z 组合键，表示输入结束

//读取文件内容：
//棍哥  25  1  99.989998
//码农宿舍  2  3  89.900002
//www.0voice.com  3  2  100.000000
