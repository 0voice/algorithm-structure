#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "getopt.h"

#define MAX_LENGTH 30 //最大成语长度，注意一个汉字在GBK编码中占两个字符
#define MAX_LINE_LENTHT 1024 //每行文本的最大长度
#define MAX_NUM 30000 //最大可支持的词典条目数
#define FILENAME_MAX_LENGTH 30 //最长文件名长度
#define DEFAULT_OUTPUT_NUM 30 //默认每次输出成语条目数
#define DEFAULT_FILENAME "idiom.txt" //默认词典文件名

void show_help();

struct list
{
    char data[MAX_LENGTH];
    bool is_visited; //标记是否已经遍历
    struct list *next;
};

struct list* create_list(char array[][MAX_LENGTH],int num);
void connect(char *input, char *output, struct list* pointer, int num, bool is_loop);

int main(int argc, char* argv[])
{
    extern int opterr, optopt;
    extern char *optarg;
    char input[MAX_LENGTH];
    char output[MAX_LENGTH];
    char idiom_array[MAX_NUM][MAX_LENGTH];
    int count = 0;
    char c;
    char init_char[4] = "";
    char filename[FILENAME_MAX_LENGTH] = DEFAULT_FILENAME;
    int show_item_num = DEFAULT_OUTPUT_NUM;
    bool is_loop  = false;
    bool is_every = false;
    struct list* ptr;
    FILE *fp;
    opterr = 0;

    while((c = getopt(argc, argv, "f:n:c:lhe")) != -1)
    {
        switch(c)
        {
        case 'f': //设置词典文件
            strcpy(filename, optarg);
            break;

        case 'n': //每次输出成语条目数
            show_item_num = atoi(optarg);
            break;

        case 'l': //是否允许循环
            is_loop = true;
            break;
        case 'e': //是否需要多次输出
            is_every = true;
            break;

        case 'h': //显示帮组文件
            show_help();
            exit(0);

        case 'c': //设定初始汉字
            strncpy(init_char, optarg, 4);
            break;

        case '?':
            printf("unrecognized option: -%c", optopt);
            show_help();
            exit(-1);
        }
    }

    fp = fopen(filename, "r");
    if(fp == NULL)
    {
    	perror("Can't open the file");
    }

    for(int i=0; i<MAX_NUM; i++)
    {
        if(!fgets(idiom_array[i], MAX_LENGTH, fp))
        {
            break;
        }

        idiom_array[i][strlen(idiom_array[i])-1] = '\0'; //删除掉换行符
        count++;
    }

    count--;
    ptr=create_list(idiom_array,count);
    if(init_char[0] == '\0')
    {
        printf("请输入一个成语\n");
        fflush(stdout);
        scanf("%s",input);
    }
    else
    {
        strncpy(input, init_char, 4);
    }

    if(is_every)
    {
        char ch = '\0';
        while(ch != 'e')
        {
            connect(input,output,ptr,show_item_num,is_loop);
            strcpy(input, output);
            ch = tolower(getchar());
            printf("\n");
        }
    }
    else
    {
        connect(input,output,ptr,show_item_num,is_loop);
        printf("\n");
    }

    fclose(fp);
    return 0;
}

struct list* create_list(char array[][MAX_LENGTH],int num)
{
    struct list *tmp1,*tmp2,*head;
    head=(struct list *)malloc(sizeof(struct list));
    strcpy(head->data,array[0]);
    head->is_visited = false;
    head->next = NULL;
    tmp1=head;

    for(int i=1; i<num; i++)
    {
        tmp2=(struct list *)malloc(sizeof(struct list));
        tmp2->next=NULL;
        strcpy(tmp2->data,array[i]);
        tmp2->is_visited = false;
        tmp1->next=tmp2;
        tmp1=tmp1->next;
    }
    return head;
}

void connect(char *input,char *output, struct list* head, int num, bool is_loop)
{
    struct list * p=head;
    int count = 0;
    char tmp[MAX_LENGTH],tmp_head[3],tmp_tail[3];
    strcpy(tmp,input);

    while(p->next!=NULL)
    {
        strncpy(tmp_tail,tmp+strlen(tmp)-2,2);
        tmp_tail[2]='\0';
        strncpy(tmp_head,p->data,2);
        tmp_head[2]='\0';

        if(strcmp(tmp_head,tmp_tail)==0)
        {
            if((!is_loop) && (p->is_visited)) //如果不允许循环，且该节点已经遍历过
            {
                p=p->next;
            }
            else
            {
                (count == 0)?printf("%s", p->data):printf(" --> %s", p->data);
                p->is_visited = true;
                strcpy(tmp,p->data);
                p=head;
                count++;

                if(count == num)
                {
                    break;
                }
            }
        }
        else
        {
            p=p->next;
        }
    }
    strcpy(output, tmp);
}

void show_help()
{
    FILE *fp = fopen("./README.md", "r");
    if(fp == NULL)
    {
        perror("Can't open the README.md\n");
        exit(-1);
    }
    char str_in[MAX_LENGTH];
    while(fgets(str_in, MAX_LENGTH, fp) != NULL)
    {
        fputs(str_in, stdout);
    }

    return;
}
