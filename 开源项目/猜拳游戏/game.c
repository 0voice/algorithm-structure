#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3

//先定义
struct user
{
	long num;
	char name[20];
	int win;
	int draw;  
	int lost;
}stu[N];

int menu();
void lianxi();
void duizhan(struct user *p);
void jifen(struct user *p);


void lianxi()
{
	int a=0,b=0,num1,num2,i;
	srand(time(0));
	printf("你有三个选择——0.出剪刀  1.出布包  2.出石头\n");
	printf("请选择。\n");
	for(i=1;i<=6;i++)
	{
		scanf("%d",&num1);
		num2=rand()%3;
		printf("%d",num2);
		if(num1==num2)
			printf("平局\n");
		else if(num1==0&&num2==1)
		{
		    printf("玩家胜\n");
		    a++;
		}
		else if(num1==1&&num2==2)
		{
			printf("玩家胜\n");
			a++;
		}
		else if(num1==2&&num2==0)
		{
			printf("玩家胜\n");
			a++;
		}
		else 
		{
			printf("电脑胜\n");
			b++;
		}
		if(a==4||b==4)
			break;
	}
	if(a>b)
		printf("你赢了！");
	else if(a==b)
		printf("打平了！");
	else
		printf("电脑赢了！");
}
int menu()
{
	int i;
	printf("|          请选择模式            |\n");
	printf("|          1.练习模式            |\n|          2.对战模式            |\n|          3.排行榜              |\n|          4.退出                |\n");
    scanf("%d",&i);
	return i;
}
void duizhan(struct user *p)
{
	int i=0;
	struct user *temporary3 = p;
	char a,b,temporary,ch;
	struct user *player1=NULL,*player2=NULL;
	printf("请输入玩家的学号与姓名：\n");
	do{
		scanf("%d%s",&p->num,p->name);
		if(i==N-1)break;
		i++;
		p++;
	}while(1);
	p =temporary3;
	for(i=0;i<N;i++)
	{
		printf("%d%s",p->num,p->name);
		p++;
	}
	p=temporary3;
	do{
				p = temporary3;
				printf("请选择对战玩家");	
					scanf("%d%d",&a,&b);
					for( i=0; i < N; i ++)   //让两个指针指向所选择的两个玩家
					{
						if(p[i].num==a||p[i].num==b)
							if(player1==NULL)
								player1 = &p[i];
							else
								player2=&p[i];
					}
					printf("游戏开始,");
					printf("你有三个选择——0.出剪刀  1.出布包  2.出石头\n");
					printf("请选择。\n");
					a = getch();
					printf("*\t");
					b = getch();
					printf("*\t");
					temporary = getchar();
					if(a==b)
						printf("平局\n");
					if(a=='0')
					{
						if(b=='1')
							{
								printf("玩家1赢了");
								player1->draw++;
								player2->draw--;
							}
						else
						{
							printf("玩家2赢了");
							player1->draw--;
							player2->draw++;
						}
					}
					if(a=='1')
					{
						if(b=='2')
							{
								printf("玩家1赢了");
								player1->draw++;
								player2->draw--;
							}
						else
						{
							printf("玩家2赢了");
							player1->draw--;
							player2->draw++;
						}
					}
					if(a=='2')
					{
						if(b=='0')
							{
								printf("玩家1赢了");
								player1->draw++;
								player2->draw--;
							}
						else
						{
							printf("玩家2赢了");
							player1->draw--;
							player2->draw++;
						}
					}
					printf("还继续玩吗（y/n）");
					//temporary =getchar();
					ch = getchar();
		}while(ch=='y');	
}
void jifen(struct user *p)
{
	int c,d,e;
	struct user temporary;
	for(c=0;c<N-1;c++)
		{
			e=c;
			for(d=c+1;d<N;d++)
			{
				if(p[e].draw<p[d].draw)
					e=d;
			}
			temporary = p[c];
			p[c] = p[e];
			p[e] = temporary;
		}
		for(c=0;c<N;c++)
		{
			printf("%d%s\n",p[c].num,p[c].name);
		}
}

void main()
{
	int chose=0;
	printf("|    欢迎参加Keve版猜拳游戏      |\n");
	while(1)
	{
		chose=menu();
		if(chose==4)
			break;
		switch(chose)
		{
		case 1:lianxi();break;
		case 2:duizhan(stu);break;
		case 3:jifen(stu);break;
		default:printf("啊哦选择0/1/2!\n");break;
		}
	}
}
