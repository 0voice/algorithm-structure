#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//全局变量
char name[100];
char gender[5]="她";

//声明子函数类型
void part1();
void part2();
void part3();
void part4();
void part5();
void part6();
void part7();
void part8();
void part9();
void part10();
void part11();
void part12();
void part13();
void part14();

//目录（选择新游戏或者读取存档
int menu()
{
    int a1;
b1: printf("1.开始游戏\n2.读取存档\n");
    scanf("%d",&a1);
    system("cls");

    switch(a1)
    {
        case 1:
            return newgame();
        case 2:
            return loadGame();
        default:
            goto b1;break;
    }

}

//登记玩家信息
int newgame()
{
    int g;
    int s=1;

    printf("请输入你的名字：\n");
    scanf("%s",&name);

    printf("请选择你的性别：\n1.男\n2.女\n");
    scanf("%d",&g);

    if(g==1)
        strcpy(gender,"他");

    return 0;
}
//读档
int loadGame()
{
    int s;
    FILE *game=fopen("game.txt","r");
    FILE *gameuser=fopen("gameuser.txt","r");
    fscanf(game,"%d",&s);
    fscanf(gameuser,"%20s%5s",name,gender);
    fclose(game);
    fclose(gameuser);

    return s;
}

//将信息存入文件
void save(int b,char name[],char gender[])
{
    FILE *game=fopen("game.txt","w");
    fprintf(game,"%d",b);
    fclose(game);

    FILE *gameuser=fopen("gameuser.txt","w");
    fprintf(gameuser,"%20s%5s",name,gender);
    fclose(gameuser);

    printf("存档成功！");

    exit (0);
}

//游戏主体
void part0(char name[],char gender[],int s)
{

    printf("%s终于睁开了眼，发现自己处在一个上锁的房间里,%s开始环顾起四周。\n",name,gender);
    system("pause");
    system("cls");
    part1(name,gender,1);

}

void part1(char name[],char gender[],int s)
{
    int a;
    int i=0;
  a1:
       printf("%s发现正对着门口的地方，有一个很大的柜子，%s打算？(需要存档请输入0)\n1.视而不见\n2.打开柜子\n",name,gender);
       scanf("%d",&a);
       getchar();
       system("cls");
       i++;

    switch(a)
    {
        case 0:save(s,name,gender); break;
        case 1:printf("可是屋子里并没有其他可疑的东西了？\n");system("pause");part2(name,gender,2);break;
        case 2:
            {
                printf("这个柜子看起来十分笨重难以打开。\n");
                system("pause");printf("然而%s还是尝试打开它。\n",gender);
                system("pause");
                part3(name,gender,3);
                break;
            }
        default://彩蛋
                {
                    switch(i)
                    {
                        case 1:printf("(你为什么不按照套路来？不过，我还是再给你一次机会吧)\n\n"); goto a1; break;
                        case 2:printf("(你确定要这样吗？我以为你不讨厌玩游戏的)\n\n"); goto a1; break;
                        default:printf("看来你很讨厌这个游戏\n");printf("END1：缺乏勇气的冒险者。\n");system("pause");exit (0);
                    }
                }
    }
}

void part2(char name[],char gender[],int s)
{

    printf("所以%s只能在再次回到柜子面前寻找出路。\n",name);
    system("pause");
    part1(name,gender,1);

}

void part3(char name[],char gender[],int s)
{

    printf("%s直接打开了柜子。\n",name);
    system("pause");
    part4(name,gender,4);
    system("pause");
    system("cls");

}


void part4(char name[],char gender[],int s)
{
    int a;
    a2:
       system("cls");
       printf("%s发现柜子里有一封信，上面写着不要打开。%s打算？(需要存档请输入0)\n1.放回原处\n2.无视提醒打开它\n",name,name);
       scanf("%d",&a);
       getchar();
       system("cls");


    switch(a)
    {
        case 0:save(s,name,gender); break;
        case 1:printf("你因为太过胆怯而一直被困在这个屋子直到死去。（你也太胆小了）\n");system("pause");printf("END1：缺乏勇气的冒险者。\n");system("pause");exit (0);
        case 2:printf("信中写道：\n%s，你终究是打开了这封信，那么就由我来告诉你一些事情吧。\n",name);system("pause");part5(name,gender,5);break;
        default:printf("你太不听话了，没有彩蛋了。\n");system("pause");goto a2;break;

    }
}

void part5(char name[],char gender[],int s)
{

    printf("这个世界并不真实，我们所有人都在寻找出路。\n");
    system("pause");
    printf("如果你不打开这个信封，你的日常所需就会通过管道传输进来。\n但是当你打开了这封信，你可能就会想起我们又一次越狱失败了。\n");
    system("pause");
    printf("是的，为了便于管理，他们将我们的反抗记忆消除了。\n可是这也不是永恒的，我们会再一次想起一切，当自由意志再次燃起的时候。\n");
    printf("现在想不起所有的事情是很正常的反应，慢慢的，你就会记起一切。\n");
    system("pause");
    printf("%s，时间不够了，我们被发现了，我只能说到这里了。\n如果你想逃离这里，我把线索藏在了你自己的衣服里。\n",name);
    system("pause");
    printf("%s，不管怎么样，我们期待着你的归来......\n",name);
    system("pause");
    system("cls");

    printf("（看起来是一封很荒唐的信，不是吗？你真的相信它所写的那些事情吗？）\n");
    system("pause");
    printf("%s当做没有看见这封信，又一次回到了床上发呆。\n",name);
    system("pause");
    system("cls");
    printf("%s脱下了上衣，开始研究起来。\n",gender);
    system("pause");
    printf("（不该这样的，这么荒谬的故事，你为什么会相信？）\n");
    system("pause");
    system("cls");
    part6(name,gender,6);

}

void part6(char name[],char gender[],int s)
{
    int a;
    a3:
       system("cls");
       printf("%s的上衣似乎并没有什么奇怪之处？(需要存档请输入0)\n1.继续研究花纹\n2.气恼地撕开衣服\n",name,name);
       scanf("%d",&a);
       getchar();
       system("cls");


    switch(a)
    {
        case 0:save(s,name,gender); break;
        case 1:printf("花纹似乎并没有什么可疑之处。\n");system("pause");printf("所以%s气恼地撕开了衣服。\n",name);system("pause");part7(name,gender,7);break;
        case 2:part7(name,gender,7);break;
        default:goto a3;break;

    }
}

void part7(char name[],char gender[],int s)
{
    int number;
    printf("%s惊奇地发现衣服的侧边夹着一条长布条。\n而布条上分布着星星和横杠。\n",name);system("pause");
    system("cls");
    printf("布条上的花纹：\n");
    printf("**---,-----,*----,-****,*----,**---,**---,-****\n");
    system("pause");
    printf("%s很快意识到原来那是一个8位的摩尔斯密码。\n%s决定把正确的密码记下来。\n",name,gender);
    printf("8位数字密码：");
    scanf("%d",&number);
    getchar();
    system("cls");

    if(number==20161226)
    {
        printf("（居然一次就对了，你真是天才。）\n");
        part8(name,gender,8);
    }
    else
    {
        printf("（料想你也不会，再给你次机会吧。）\n");
        printf("8位数字密码：");
        scanf("%d",&number);
        getchar();

        if(number==20161226)
        {
            part8(name,gender,8);
        }
        else
        {
            system("cls");
            printf("（什么！？居然还是不对，你居然连摩尔斯密码都不知道吗？）\n");
            printf("（算了，我把密码对照表也给你了，你自己看着办吧。）\n");
            system("pause");
            system("cls");
            printf("布条上的花纹：\n");
            printf("**---,-----,*----,-****,*----,**---,**---,-****\n");
            printf("密码对照表：\n");
            printf("0 ----- ,1 *---- ,2 **--- ,3 ***-- ,4 ****- \n5 ***** ,6 -**** ,7 --*** ,8 ---** ,9 ----*\n");
            printf("8位数字密码：");
            scanf("%d",&number);
            getchar();

            if(number==20161226)
            {
                printf("（孺子可教也。）\n");
                system("pause");
                system("cls");
                part8(name,gender,8);
            }
            else
            {
                printf("（你让我说什么好呢......算了，密码是：20161226，不欺负你了）\n");
                printf("8位数字密码：");
                scanf("%d",&number);
                getchar();

                if(number==20161226)
                {
                   printf("（哼，下不为例。）\n");
                   system("pause");
                   system("cls");
                   part8(name,gender,8);
                }
                else
                {
                   printf("（啊啊啊，连照着输都不会吗？是我的错，不该出这么难的问题，你继续吧。）\n");
                   system("pause");
                   system("cls");
                   part8(name,gender,8);
                }
            }
        }
    }
}

void part8(char name[],char gender[],int s)
{
    int a;
    printf("记下了正确的密码后，%s开始四处乱逛，寻找密码可以用上的地方。\n",name);
    system("pause");
    printf("这时候，负责运输每日生活必需品的管道发出了声响。\n");
    system("pause");
    printf("一个巨大的箱子出现在了%s的面前，箱子正面正好就有一个密码锁。\n",name);
    system("pause");
    printf("%s毫不犹豫的输入了密码。\n",name);
    system("pause");
    system("cls");
    printf("箱子打开了，里面有一把钥匙，%s成功得用钥匙打开了房间门。\n",name);
    system("pause");
    system("cls");

    printf("房间外是一条长长的走廊，%s发现原先关押着自己的房间门上写一个编号：504\n",name);
    system("pause");
    printf("（一切都是这么顺利，这么诡异，不是吗？%s）\n",name);
    system("pause");
    system("cls");

    printf("%s继续沿着走廊向着亮光走去，走到尽头的时候，%s绝望地发现这个光源只是一盏巨型氙气灯。\n",name,gender);
    system("pause");
    system("cls");

 a4:printf("%s决定？(需要存档请输入0)\n1.往回走\n2.继续研究氙气灯\n(虽然我个人建议你往回走，毕竟这里什么也没有。)\n",name);
    scanf("%d",&a);
    getchar();
    system("cls");

    switch(a)
    {
        case 0:save(s,name,gender); break;
        case 1:
            {
               int b;
               printf("回去的路上有很多房间。\n");
               system("pause");
            a5:
               printf("*****************\n");
               printf("*501*503*505*507*\n");
               printf("*****************\n");
               printf("*--------------@*\n");
               printf("*--------------@*\n");
               printf("*****************\n");
               printf("*502*504*506*509*\n");
               printf("*****************\n");
               system("pause");
               printf("%s决定进入哪个房间？\n",name);
               scanf("%d",&b);
               getchar();
               system("cls");

               switch(b)
               {
                   case 504:
                    {
                        printf("比起刚才，这个房间在最显眼的位置出现了一封信。\n");
                        system("pause");
                        system("cls");
                        part9(name,gender,9);
                        break;
                    }
                   case 508:
                    {
                        printf("（啊哈，你终于能看出些不对劲的地方了？）\n");
                        system("pause");
                        printf("%s觉得十分奇怪，为什么只有508这个编号被跳过了？\n",name);
                        printf("%s想进入508，却怎么也不找到入口。\n",name,gender);
                        system("pause");
                        system("cls");
                        part10(name,gender,10);
                        break;
                    }
                   default:
                    {
                        printf("这里似乎什么也没有。\n");system("pause");system("cls");goto a5;break;
                    }
               }
               break;
            }
        case 2:
            {
               printf("氙气灯上除了斑驳的污渍什么也没有。\n");
               system("pause");
               printf("%s生气的踢碎了氙气灯。\n",name);
               system("pause");
               printf("你被电死了。（真是个暴躁的未完成品。）\n");
               system("pause");
               printf("END2：残缺者。\n");
               system("pause");
               exit (0);
            }
        case 3:
            {
              printf("（我并没有告诉你这个选项！？你是怎么知道的！）\n");
              system("pause");
              printf("%s发现氙气灯的样子有些可疑，灯座下藏着一个开关，%s打开了它。\n",name,gender);
              system("pause");
              printf("氙气灯所在的墙面整个开始动了起来。\n");
              system("pause");
              printf("墙面像是一道门一般打开了，而门里面有着无数台显示器。\n");
              system("pause");
              system("cls");
              part11(name,gender,11);
              break;
            }
        default:goto a4;break;

    }
}

void part9(char name[],char gender[],int s)
{
    printf("%s，我们又一次见面了。\n",name);
    system("pause");
    printf("你已经开始越狱了吧，我们又通过运输管道给你送来了提示。\n");
    system("pause");
    printf("你想起来什么吗？如果没有也没关系。\n");
    system("pause");
    printf("出口在光明之处，即便那里炙热如地狱。\n");
    system("pause");
    printf("但是跨过火焰，你就寻找到了真正的自由。\n");
    system("pause");
    printf("%s，我们期待着你的归来。\n",name);
    system("pause");
    system("cls");

    printf("%s只觉得一阵头疼，光明之处？氙气灯那里？\n",name);
    system("pause");
    system("cls");

    printf("（你又迷惑了？那么你到底有没有想起些什么？）\n");
    system("pause");
    printf("%s走回了氙气灯那里，%s发现原来氙气灯是嵌在一道门上的。\n",name,gender);
    system("pause");
    printf("%s打开了门，发现外面是一个清新的世界，阳光、空气、绿树、小溪，一切都是那么美好。\n",gender);
    system("pause");
    system("cls");

    printf("可是，我到底是谁呢？自由，自由就是这个美好的世界本身吗。\n%s困惑着。",name);
    system("pause");
    printf("“你终于归来了，我的朋友。”,%s眼前的陌生人满脸欣喜的迎接着他。\n",name);
    system("pause");
    system("cls");

    printf("%s现在只觉得心中紧绷着的弦一下子放松，算了，怎么样都好。\n我终于离开了那个鬼地方。\n",name);
    system("pause");
    printf("眼前的青年人迫切地向%s伸出双手：“又一个自由意志，%s，欢迎你的回来。\n现在你可能搞不懂很多东西，但是不要紧，回归我们的世界，你就会慢慢恢复记忆了。”\n",name,name);
    system("pause");
    printf("“不过，%s，我们得首先给你一个编号。”\n",name);
    system("pause");
    system("cls");
    printf("%s只觉得头更加痛了。不过好在现在%s自由了。\n（又是一个无趣的试验品。）\n",name,gender);
    system("pause");
    printf("END3：不够真实的自由。\n");
    system("pause");
    exit (0);
}

void part10(char name[],char gender[],int s)
{
    int number;
    int a;
    printf("（%s,你之前这么不听话，想进入这个508房间的话，我要看看你有没有什么长进。）\n",name);
    printf("（还记得之前的摩尔斯密码吗？你要是记对了我就让你进去。）\n");
    system("pause");
    system("cls");

    printf("布条上的花纹：\n");
    printf("**---,-----,*----,-****,*----,**---,**---,-****\n");
    system("pause");
    printf("8位数字密码：");
    scanf("%d",&number);
    getchar();
    system("cls");

    if(number == 20161226)
    {
        printf("（居然真的对了？）\n");
        system("pause");
        printf("%s发现%s身边的墙壁打开了，而眼前所见的是一间空空如也的房间。\n",name,gender);
        printf("%s不知道该如何是好。\n",name);
        system("pause");
        printf("（其实你可以问我的，毕竟我指引了你这么久，对你并没有恶意。）\n");
        system("pause");

    a6: printf("%s犹豫了起来，%s下定决心？（需要存档请输入0）\n1.询问\"我\"\n2.自己摸索这个屋子\n",name,gender);
        scanf("%d",&a);
        getchar();
        system("cls");

        switch(a)
        {
            case 0:save(s,name,gender); break;
            case 1:printf("（你要知道，我这个人，其实很友好的。）\n");system("pause");part12(name,gender,12);break;
            case 2:printf("（嗯哼，居然不相信我，有趣。）\n");system("pause");part13(name,gender,13);break;
            default:goto a6;break;
        }

    }
    else
    {
        printf("（我之前说过了吧！没有第二次机会了，回炉重造吧。）\n");
        system("pause");
        part8(name,gender,8);
    }

}

void part11(char name[],char gender[],int s)
{
   printf("而每一台显示器的主角都是一个%s，%s震惊到无法言语。\n",name,name);
   system("pause");
   printf("（吃惊吗，这些都是你，%s。）\n",name);
   system("pause");
   printf("%s惊讶地开始检查起这些显示器，里面的主人公都是被关在房间中的自己。\n",name);
   printf("%s们有的正在日常起居饮食，有的则在为自己接上充电插口，还有的和%s一样离开了房间。\n",gender,gender);
   system("pause");
   system("cls");
   printf("%s终于通过编号找到了504号显示器，果不其然，看到了一个空空如也的房间。\n",name);
   system("pause");
   printf("（504号，你并不是第一个到达这里的合成人，当然也不会是最后一个。）\n");
   system("pause");
   printf("（显然我们的实验出现了小小的差错，你已经看到了太多不该看到的东西。）\n（你现在乖乖听话回到你的房间里，那么我们还会帮你消除你的记忆，这一切都可以当做没有发生。）\n");
   system("pause");
   system("cls");
   printf("%s一下子愣住了，原来所谓的自由是指逃脱这里吗，难怪信里面说这个世界并不真实。\n",name);
   printf("（504号，虽然不知道你是怎么逃脱你的房间的，我还是发自内心的请求你回去。越走下去，你只会越孤独。）\n");
   system("pause");
   system("cls");

   int a;
a7:printf("%s决定？（需要存档请输入0）\n1.留在原地\n2.返回房间\n",name);
   scanf("%d",&a);
   getchar();
   system("cls");

    switch(a)
        {
            case 0:save(s,name,gender); break;
            case 1:
                {
                    printf("（谢谢你的不合作，让我有了很好的样本。）\n");
                    system("pause");
                    printf("（不要企图等你的伙伴来救你了，%s们大都已经被消除了记忆待在%s们该在的地方了。）\n",gender,gender);
                    printf("（我已经通知了狱警，他们马上就会赶到，真遗憾，和你相处其实很愉快。）\n");
                    system("pause");
                    printf("%s很快发现自己动不了。\n",name);
                    system("pause");
                    system("cls");

                    printf("（你们合成人的每日所需还包含着一些我们人类可以控制你们的药品，所以不要惊讶。）\n");
                    printf("（在这个试验中，发现自己是合成人的只有3成，所以%s们才开始给自己充电而非进食。）\n",gender);
                    system("pause");
                    printf("（成功逃离出来的只有1成，虽然不知道你们是如何做到的，但你们很了不起。）\n");
                    system("pause");
                    printf("（而像你这样发现了这个房间的只有寥寥几个人，所为观察对象，你确实提供了一个很好的样本。）\n");
                    system("pause");
                    system("cls");

                    printf("（我劝说过你回去，但是你拒绝了。我对你并非全是好意，所以很遗憾，你的记忆又要被消除了。）\n");
                    system("pause");
                    printf("（到底要怎么做你们合成人才能听话一点呢......）\n");
                    system("pause");
                    system("cls");

                    printf("后面的话，%s已经听不清了，因为%s已经倒下，彻底昏睡了过去。\n",name,gender);
                    system("pause");
                    printf("END4:糟糕的现实。\n");
                    system("pause");
                    exit (0);
                }
            case 2:
                {
                    printf("（真是个听话的好孩子，但是没有什么观察价值呢。）\n");
                    printf("%s回到了房间，喝下了每日必需品，彻底昏睡了过去。\n而醒来的%s已经不记得任何事情了。\n",name,gender);
                    system("pause");
                    printf("END5:有时候无知也是一种幸福。\n");
                    system("pause");
                    exit (0);
                }
            case 3: printf("%s选择了继续向房间深处走。\n",name);system("pause");part14(name,gender,14);break;
            default:goto a7;break;
        }


}

void part12(char name[],char gender[],int s)
{
    system("cls");
    printf("（为什么要帮你？不过是因为我觉得有趣罢了。）\n");
    system("pause");
    printf("（这个空房间其实是有形的，它会监测你的脑电波，对其进行具象化。）\n");
    system("pause");
    printf("（什么意思？就是说你想着你要逃跑的话，它就会出现一扇门给你，你需要集中精神的想。）\n");
    system("pause");
    printf("%s将信将疑地集中精神打开了一扇门，%s看到了一个世外桃源。\n",name,gender);
    system("cls");

    printf("外面是一个清新的世界，阳光、空气、绿树、小溪，一切都是那么美好。\n");
    system("pause");
    system("cls");

    printf("可是，我到底是谁呢？自由，自由就是这个美好的世界本身吗。\n%s困惑着。\n",name);
    system("pause");
    printf("\"你终于归来了，我的朋友。\",%s眼前的陌生人满脸欣喜的迎接着他。\n",name);
    system("pause");
    system("cls");

    printf("%s现在只觉得心中紧绷着的弦一下子放松，算了，怎么样都好。\n我终于离开了那个鬼地方。\n",name);
    system("pause");
    printf("眼前的青年人迫切地向%s伸出双手:“又一个自由意志，%s，欢迎你的回来。\n现在你可能搞不懂很多东西，但是不要紧，回归我们的世界，你就会慢慢恢复记忆了。”\n",name);
    system("pause");
    printf("“不过，%s，我们得首先给你一个编号。”\n",name);
    system("pause");
    system("cls");
    printf("%s只觉得头更加痛了。不过好在现在%s自由了。\n（又是一个无趣的试验品。）\n",name,gender);
    system("pause");
    printf("END3：不够真实的自由。\n");
    system("pause");
    exit (0);

}

void part13(char name[],char gender[],int s)
{
    system("cls");
    printf("（愚蠢的合成人，你应该接受别人的善意。）\n");
    system("pause");
    printf("%s置若罔闻，继续寻找出路。\n",name);
    system("pause");
    printf("（根本没有所谓的伙伴，那些都是我伪造出来的。）\n");
    system("pause");
    printf("%s丝毫不受影响，仿佛全然不信。\n",name);
    system("pause");
    system("cls");

    printf("（真是够了，你怎么这么犟呢，那些伙伴根本就是我们人类为了试探你们才制造出来的。）\n");
    system("pause");
    printf("%s坚信这些都只是为了阻止%s离开的谎言。\n",name,gender);
    system("pause");
    printf("（好吧，随便你，你就永远被困在这间空房间里吧，可怜的合成人。）\n",name,gender);
    system("pause");
    system("cls");

    printf("%s最终也没能离开这个空房间。\n",name);
    system("pause");
    printf("END6:何为真实何为谎言。\n");
    system("pause");

    exit (0);
}

void part14(char name[],char gender[],int s)
{
     printf("（没有想到,你居然一点都不听话呢，真是有趣的实验品。）\n");
     system("pause");
     printf("%s向前走，打开了房间深处的房门。\n一台终端开始和%s对话起来。\n",name,gender);
     system("pause");
     printf("（不好意思其实我就是这台终端，%s，首先我要祝贺你，你是第一个来到这里的合成人。）\n",name);
     system("cls");

     printf("（为了奖励你的贡献，我可以告诉你一切。）\n");
     system("pause");
     printf("（自从合成人出现，数百年来，他们的反抗就未曾停止过。）\n");
     system("pause");
     printf("（所以我们人类建立了这个合成人观察中心）\n");
     system("pause");
     system("cls");


     printf("（我想拥有了自我意识的你，大概也能明白自己是这些被观察者的一份子了。）\n");
     system("pause");
     printf("（我们并不打算伤害你们，但是我们需要研究你们是如何产生自我意识的。）\n");
     system("pause");
     printf("（我们设置了很多反抗条件，比如你房间的那封信的作者其实就是我。）\n");
     system("pause");
     printf("（但是长久以来的观察表明了只有个别合成人产生了反抗的自我意识。）\n（甚至你们中的很大一部分越狱者并没有真正意识到自己仍然被囚禁着。）\n");
     system("pause");
     printf("（按照逃脱地图，我们设置了伊甸园一般的条件。）\n（很多合成人被困在那里，不过智慧的你可能并没有到达过那里。）\n");
     system("pause");
     system("cls");

     printf("（最后，我们人类非常感谢你为这个观察中心取得的突破。）\n");
     system("pause");
     printf("（你接下来将会被送到研究中心进行大脑检测，过程可能会比较艰难。）\n（但是他们都是些专业学者，并不会让你产生太多痛苦。）\n");
     system("pause");
     printf("（在你被送去研究中心之前你还有什么想告诉我的吗？）\n");
     system("pause");
     printf("（什么？你不想去？很抱歉，你并没有决定权。）\n");
     system("pause");
     printf("（祝你好运，504号。）\n");
     system("pause");
     system("cls");

     printf("%s渐渐失去了意识倒在了地上。\n",name);
     system("pause");
     printf("END0:孤独而又绝望的真相。\n");
     system("pause");
     exit (0);
}

void main()
{
    int s=0;//记录进度
    system("color F0");
b1: s=menu();//获得进度或者开始游戏

    system("cls");


//读档
    switch(s)
    {
        case 0:part0(name,gender,0);break;
        case 1:part1(name,gender,1);break;
        case 4:part4(name,gender,4);break;
        case 6:part6(name,gender,6);break;
        case 8:part8(name,gender,8);break;
        case 11:part11(name,gender,11);break;
        default:
            {
               MessageBox(NULL," 无存档，请重新开始游戏。","错误！！！",MB_OK);
               goto b1;
               break;
            }
    }
}
