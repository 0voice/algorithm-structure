  
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <time.h>
#define maxn 5

enum thetest{OK=0,NO=1,QUIT=2,AGAIN=3};
enum kind{fp=0,mh=1,heit=2,hongt=3};
struct feature{
    int num;
    enum kind kin;
}card[52];                                        //写牌
const char * suit(struct feature i){              //记录扑克牌的花色
    if(i.kin==0)return"方片";
    else if(i.kin==1)return"梅花";
    else if(i.kin==2)return"黑桃";
    else return"红桃";
}
char * number(struct feature i){                  //记录扑克牌数值
    char *c= (char*)malloc(sizeof(char)*3);
    memset(c,0,sizeof(char)*3);
    if(i.num==1)
        c[0] = 'A';
    if(i.num>1&&i.num<10){
        c[0] = (char)i.num+(char)'0';
    }
    if(i.num==10)
        c[0]='1',c[1]='0';
    if(i.num==11)
        c[0]='J';
    if(i.num==12)
        c[0]='Q';
    if(i.num==13)
        c[0]='K';
    return c;
}
void playingcards(struct feature card[]){       //初始化牌库
    for(int i=0;i<=3;i++){
        for(int n=1;n<=13;n++){
            card[i*13+n-1].num=n;           //但是数值JOK并未重新定义
            card[i*13+n-1].kin=i;
        }
    }

}
void shuffle(struct feature a[],int n){       //使用洗牌算法 洗牌
    for(int i=0;i<n;i++){
        int tab=rand()%(n-i)+i;
        struct feature tab1;
        tab1=a[i];
        a[i]=a[tab];
        a[tab]=tab1;
    }
}
int choose(char *str){                         //设置两名玩家执行的操作
    if(strlen(str)==1){
        if(str[0]=='y')return OK;
        else if(str[0]=='n')return NO;
        else if(str[0]=='q')return QUIT;
        else return AGAIN;
    }
    else return AGAIN;
}
int wager(char *str){                        //用于判断是否需要继续进行筹码押注
    if(str[0]=='y')return OK;
    if(str[0]=='n')return NO;
}
int main(){
    printf("*********************这是21点游戏*********************\n");
    int winner=0;
    int money[2];
    memset(money,0,sizeof(money));       //初始化总筹码
    money[0]=2500;
    money[1]=2500;
    int cash[2];                         //初始化押金
    memset(cash,0,sizeof(cash));
    int run=0;                   //开始
    while(run==0){             //设置是否重新开始游戏，   游戏正式开始，程序大框架
        int nsize=0;            //记录选n的次数，如果两人都选n游戏直接进入比分环节
        int n=0;                //准备从牌库中抽取卡牌
        int tip=0;              //程序关键，用于判断是否需要结束本局游戏，开启下一局游戏
        int score[2];            //记录两人的积分
        memset(score,0,sizeof(score));      //积分初始化
        char str[10];
        playingcards(card);               //初始化牌库
        srand((unsigned)time(NULL));
        shuffle(card,52);                   //洗牌
        printf("游戏即将开始!\n");
        if(money[0]>0&&money[1]>0){
            printf("请两名玩家分别选择需要押注的筹码数，现在通知筹码个数：\n");
            printf("玩家1拥有%d筹码，玩家2拥有%d筹码\n",money[0],money[1]);
            printf("现在请玩家1下注，请输入你押注的筹码\n");
            scanf("%d",&cash[0]);
            money[0]-=cash[0];
            printf("现在请玩家2下注，请输入你押注的筹码\n");
            scanf("%d",&cash[1]);
            money[1]-=cash[1];
        }         //押注以及判断筹码环节
        printf("这是本次游戏的第一个回合，现在分发给两名玩家第一张手牌\n");
        for(int j=1;j<=2;j++){                           //第一回合两人必须摸牌
            char *num =number(card[n]);
            score[j-1]+=card[n].num;
            printf("玩家%d，您的起始手牌是：%s%s，您的起始积分是:%d\n",j,suit(card[n]),num,score[j-1]);
            n++;
        }
        for(int i=1;i<=2;i++){                       //回合开始，实现两人轮流抽牌
            printf("\n请玩家%d选择是否抽一张牌,y/n/q\n",i);
            while(tip==0){                        //当tip=0意味本次游戏继续进行，tip=1是本次游戏结束的标识
                scanf("%s",str);                   //输入方案 y/n/q
                if(choose(str)==AGAIN)continue;
                else if(choose(str)==QUIT){
                    printf("玩家%d选择认输，游戏结束。本次胜利的玩家是 玩家%d\n",i,3-i);
                    tip = 1;                     //有一名玩家失败，本轮游戏结束
                    winner=3-i;
                    break;
                }
                else if(choose(str)==NO){
                    nsize++;                   //选n次数上升
                    if(i==2&&nsize!=2)nsize=0;
                    printf("您本轮选择不抽牌\n");
                    printf("您现在的积分为：%d\n",score[i-1]);
                    break;                       //break掉while tip，下一个人
                }
                else{
                    nsize=0;
                    char *num = number(card[n]);
                    printf("你本轮抽取的卡牌为：%s%s\n",suit(card[n]),num);
                    free(num);
                    if(card[n].num>10)
                        card[n].num=10;
                    score[i-1]+=card[n].num;
                }
                printf("您现在的积分为%d\n",score[i-1]);
                n++;                      //继续发牌
                if(score[i-1]>=21){
                    printf("玩家%d，很遗憾您爆了，您输了。本次胜利的玩家是 玩家%d\n",i,3-i);
                    tip=1;
                    winner=3-i;
                    break;
                }
                break;
            }
            if(nsize==2){
                tip=1;
                if(score[0]==score[1]){
                    winner=0;
                    printf("本次游戏两人平局\n");
                }
                else if(score[0]>score[1]){
                    printf("本次胜利的玩家是 玩家1\n");
                    winner=1;
                }
                else{
                    printf("本次胜利的玩家是 玩家2\n");
                    winner=2;
                }
            }
            if(tip==1&&winner!=0){
                money[winner-1]=money[winner-1]+cash[0]+cash[1];
                break;
            }
            if(tip==1&&winner==0){
                money[0]=money[0]+cash[0];
                money[1]=money[1]+cash[1];
                break;
            }
            if(i==2)i=0;
        }
        printf("本次游戏已经结束，现在公布最新筹码个数：\n玩家1拥有%d筹码,玩家2拥有%d筹码\n",money[0],money[1]);
        if(money[0]==0){
            printf("玩家1请离场，玩家2彻底胜利，拥有总共5000筹码");
            run=1;
            break;
        }
        if(money[1]==0){
            printf("玩家2请离场，玩家1彻底胜利，拥有总共5000筹码");
            run=1;
            break;
        }
        if(money[0]!=0&&money[1]!=0){
            char goon[5];
            int signal=0;
            for(int i=1;i<=2;i++){
                printf("请玩家%d选择是否要继续进行游戏并押注y/n",i);
                scanf("%s",goon);
                if(wager(goon)==0)signal++;
            }
            if(signal!=2){
                run=1;
                printf("*********************游戏结束*********************\n");
                break;
            }
            if(signal==2){
                printf("*********************游戏继续*********************\n");
            }
        }
    }
    system("pause");
    return 0;
}
