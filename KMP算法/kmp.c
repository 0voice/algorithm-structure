#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ERROR 0;
#define TRUE 1;
//初始化数据
int InitData(char **source,char **target,int **value){

    char ch;
    int i = 0;

    (*source) = (char *)malloc(sizeof(char) *100);
    (*target) = (char *)malloc(sizeof(char) *100);
    (*value) = (int *)malloc(sizeof(int) *100);


    if(!(*source) || !(*target) || !(*value))return ERROR;

    printf("请输入要输入源字符串,以#结束:\n");

    while((ch = getchar())!='#'){

        (*source)[i++] = ch;
        (*source)[i] = '\0';
    }
    getchar();  //抵消缓冲

    i = 0;  //重置
    printf("请输入要匹配的字符串,以#结束:\n");

    while((ch = getchar())!='#'){
        (*target)[i++] = ch;
        (*target)[i] = '\0';
    }

    //初始化value数组
    for(i = 0; i < 100;i++){
        (*value)[i] = 0;
    }
    return TRUE;
}


//得出target中的匹配值
int GetValue(char * target, int *value){  

    char *head,*tail;
    int temp;
    //ABCDABD
    //ABCDAB
    int i = 1,j = 0;
    head = (char *)malloc(sizeof(char) *100);
    tail = (char *)malloc(sizeof(char) *100);
    if(!head || !tail)return ERROR;

    for(i = 1;i<strlen(target);i++){  //从头到尾

        j = 0;
        while(target[j]!='\0'){  //复制到临时数组
            head[j] = target[j];
            tail[j] = target[j];
            j++;
            head[j]='\0';
            tail[j] = '\0';
        }

        head[i] = '\0';
        tail[i+1] = '\0';

        for(j = 0;j<i;j++){
            if(strcmp(head,tail+1+j)==0){  //比较
                value[i] = strlen(head);
                break;
            }
            temp = strlen(head) - 1;
            head[temp] = '\0';
        }
    }
}

//KMP处理过程
int KMP(char *source,char *target,int *value){

    int i = 0,j = 0;

    while(i < strlen(source)){  //不回溯，source走到尾

        if(source[i] == target[j] && j<strlen(target)){
            i++;
            j++;
        }else if(j>=strlen(target)){
            printf("找到...");
            return TRUE;

        }else if(source[i]!=target[j]){
            if(j==0){
                j=0;
                i++;
            }else{
                j =  value[j-1];
            }
        }
    }
    if(i >=strlen(source) && j>=strlen(target))printf("找到...");
    else printf("未找到...");
    return ERROR;
}
int main(){
    char *source,*target; //source源字符串，target要匹配的字符串
    int *value;  //存放匹配值
    int i = 0;

    InitData(&source,&target,&value);  //初始化字符串
    GetValue(target,value);
    KMP(source,target,value);
}
