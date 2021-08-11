#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max 6
int main()
{
    char Hname[50];//皇帝名称
    int choice;//皇帝选择
    int count=5;
    int i,j,m,temp;
    char te[30];
    char spname[30];//皇帝要翻牌的妃子
    char badname[30];//打入冷宫的妃子
    int serchindex=-1;//打入冷宫的妃子下标
    char flname[30];//赏花的妃子
    char names[max][30]= {"不知火舞","西施","安琪拉","杨玉环","珍妮"}; //初始的妃子姓名
    char levelsname[5][20]= {"小主","贵人","嫔妃","贵妃","皇后"}; //级别的名称
    int levels[max]= {1,3,0,1,2,-999}; //给前五位定的初始级别，第六位未知
    int loves[max]= {100,100,100,100,100,-9999}; //初始好感都是100，除了最后一位未知

    printf("请输入皇帝的名号：\n");
    scanf("%s",Hname);
    getchar();
    printf("%s皇帝登基，皇帝万岁万岁万万岁！\n",Hname);
    printf("**************皇帝和他的爱妃************\n");
    printf("姓名\t\t级别\t\t好感度\n\n");
    for(i=0; i<count; i++)
    {
        printf("%-12s\t%s\t\t%d\n",names[i],levelsname[levels[i]],loves[i]);
    }
    printf("\n***************************************\n");

    printf("1.皇帝下旨选妃.\t\t(增加妃子)\n");
    printf("2.皇帝翻牌宠幸.\t\t(修改状态)\n");
    printf("3.妃子打入冷宫.\t\t(删除妃子)\n");
    printf("4.皇帝单独召见.\t\t(修改状态)\n");
    printf("5.查看所有妃子.\t\t(查查查查)\n");

    for(j=0; i<20; j++)
    {
        printf("\n请皇帝选择要干的事情:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("***************************************\n");
            if(count<max)
            {
                printf("请输入要选的妃子的姓名：");
                scanf("%s",names[count]);
                levels[count]=0;
                loves[count]=100;
                count++;
            }
            else
            {
                printf("皇上你要保重龙体，后宫已经住不下了\n");
            }

            break;
        case 2:
            printf("\n***************************************\n");
            printf("今天惠风和畅是个好日子，朕要到某个宫要和某位妃子一起用膳，她是:");
            scanf("%s",spname);
            //寻找到那个妃子然后给她好感度加十，级别加一，其他人好感减十。
            for(i=0; i<count; i++)
            {
                if(strcmp(names[i],spname)==0)
                {
                    loves[i]+=10;
                    levels[i]=levels[i]>=4?4:levels[i]+1;//这里要判断级别加一的时候不能超过最大值。
                }
                else
                {
                    loves[i]-=10;
                }
            }
            break;
        case 3:
            printf("\n***************************************\n");
            printf("今天真差劲儿，某位妃子把皇上惹生气了，要把她打入冷宫，她是:");
            scanf("%s",badname);
            //寻找到那个妃子然后给她删除，其他人好感增加10。
            for(i=0; i<count; i++)
            {
                if(strcmp(names[i],badname)==0)
                {
                    serchindex=i;
                    break;
                }
            }
            if(serchindex==-1)
            {
                printf("幸好宫里没有这个妃子，皇上记错了，我们继续玩乐\n");
            }
            else
            {
                for(i=0; i<count; i++)
                {
                    loves[i]+=10;
                }
                for(i=serchindex; i<count-1; i++) //后一个赋值给前一个，注意对应的东西也要赋值好。
                {
                    strcpy(names[i],names[i+1]);
                    loves[i]=loves[i+1];
                    levels[i]=levels[i+1];
                }
                count--;
            }
            break;
        case 4:
            printf("\n***************************************\n");
            printf("今天皇上心血来潮，要和某位妃子一起去御花园赏花，她是:");
            scanf("%s",flname);
            //寻找到那个妃子然后给她好感度加十，级别加一，其他人好感减十。
            for(i=0; i<count; i++)
            {
                if(strcmp(names[i],flname)==0)
                {
                    loves[i]+=10;
                    levels[i]=levels[i]>=4?4:levels[i]+1;//这里要判断级别加一的时候不能超过最大值。
                }
                else
                {
                    loves[i]-=10;
                }
            }
            break;
        case 5:
            printf("\n***************************************\n");
            printf("\n皇帝请查看后宫所有的妃子(1.默认排序;2.按照级别排序;)：\n");
            scanf("%d",&m);
            if(m==1)
            {
                printf("按照默认顺序排序是：\n");
                printf("姓名\t\t级别\t\t好感度\n\n");
                for(i=0; i<count; i++)
                {
                    printf("%-12s\t%s\t\t%d\n",names[i],levelsname[levels[i]],loves[i]);
                }
            }
            else//使用冒泡排序,交换他们的姓名，好感和级别。
            {
                for(i=0; i<count; i++)
                {
                    for(j=0; j<count-1-i; j++)
                    {
                        if(levels[j]<levels[j+1])
                        {
                            temp=levels[j];
                            levels[j]=levels[j+1];
                            levels[j+1]=temp;
                            temp=loves[j];
                            loves[j]=loves[j+1];
                            loves[j+1]=temp;
                            strcpy(te,names[j]);
                            strcpy(names[j],names[j+1]);
                            strcpy(names[j+1],te);
                        }
                    }
                }
                printf("按照级别顺序排序是：\n");
                printf("姓名\t\t级别\t\t好感度\n\n");
                for(i=0; i<count; i++)
                {
                    printf("%-12s\t%s\t\t%d\n",names[i],levelsname[levels[i]],loves[i]);
                }
            }
            break;
        default:
            printf("请陛下再次确认要干的事情！！\n");
        }
    }
    return 0;
}
