//  chess.c
//
//  Created by zigzagpig on 15/3/12.
//  Copyright (c) 2015年 zigzagpig. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char chess_in[20][20];          // 存放棋盘信息
int colour[20][20] = { 0 };		//纪录格子棋子的颜色 0:红子或空 1:黑子
char basic_word[50][50];        // 存放关键字，如车马炮等，因为字符类型不支持汉字
int x,x_offset,y,y_offset;      // x：当前棋子所在行数 x_offset：移动棋子要偏移的行向量 y,y_offset：也一样，对应的是列
int win = 0 ;                   //	0:未胜利 1:胜利
int turn = 0;	                //	0:红方回合 1:黑方回合
int step = 0;                   //  纪录步数
int i,j;                        //  临时变量，FOR循环要用到
FILE *out;                      //  文件指针，打开一个全局文件，存放棋谱

int show()                                                  //  把当前棋盘展示出来
{
    printf("1 2 3 4 5 6 7 8 9\n" );                         //  打印标准纪录棋谱棋盘上方的数字
    for ( i = 0; i < 10; ++i)                               // 10行9列棋盘
    {
        for ( j = 0; j < 9; ++j)
            printf("%s", basic_word[chess_in[i][j]-'a']) ;  //  打印棋子对应的汉子
        printf("\n");
        if(i == 4)                                          //  在棋盘中间打印 楚河 汉界
        {
            for ( j = 0; j < 9; ++j)
                printf("%s", basic_word[chess_in[10][j]-'a']) ;
            printf("\n");
        }
    }
    printf("九八七六五四三二一\n" );                            //  打印标准纪录棋谱棋盘下方的数字
    return 0;
}

int move_is_ok()                                            //  当棋子是否符合移动规则
{
    return  chess_in[x][y] != 'a' 	                        //该位置有子
    && colour[x][y] == turn 		                        //正当改棋子方在动
    && ( x >= 0 && x < 10  ) 					            //移动后未出界
    && ( y >= 0 && y < 9 )
    && ( x+x_offset >= 0 && x+x_offset < 10  )
    && ( y+y_offset >= 0 && y+y_offset < 9 )
    && (( chess_in[x+x_offset][y+y_offset] != 'a' && colour[x+x_offset][y+y_offset] != turn )
        || chess_in[x+x_offset][y+y_offset] == 'a' ) ;      //不能杀自己人
}

int is_win()                                                //  是否结束游戏
{
    if ( chess_in[x+x_offset][y+y_offset] == 'j' ||
        chess_in[x+x_offset][y+y_offset] == 'k' )
    {
        printf("-----------\n%s被吃了，游戏结束\n", basic_word[ chess_in[x+x_offset][y+y_offset] - 'a' ] );
        win = 1;
    }
    
    return 0;
}

int pu()                                                    //  记谱功能
{
    int record_abs;                                         //  纪录要偏移的行绝对值
    record_abs = x_offset;
    if ( x_offset < 0 )
        record_abs = - x_offset;
    fprintf(out,"%03dth ",step );                           //  打印步数
    printf("\n\n\n%dth ",step );
    if ( turn == 0 )                                        //  红方情况
    {
        printf("红: ");                                     //  打印如“红: 车一平二”的    红
        fprintf(out,"红: ");
        printf("%s",basic_word[chess_in[x][y] - 'a'] );     //  打印如“红: 车一平二”的    车
        fprintf(out,"%s",basic_word[chess_in[x][y] - 'a'] );
        printf("%s",basic_word[ y + 19 ] );                 //  打印如“红: 车一平二”的    一
        fprintf(out,"%s",basic_word[ y + 19 ] );
        if ( x_offset == 0 )
        {
            printf("平%s",basic_word[ y + y_offset + 19 ] );//  打印如“红: 车一平二”的    平二
            fprintf(out,"平%s",basic_word[ y + y_offset + 19 ] );
        }
        else
        {
            if ( x_offset < 0 )                             //  打印如“红: 车一平二”的    不 平 就是   进 退  
            {
                printf("进");
                fprintf(out,"进");
            }
            else
            {
                printf("退");
                fprintf(out,"退");
            }    
            if (        ( chess_in[x][y] >= 'b' &&  chess_in[x][y] <= 'e')              //  若不是马象士的情况
                    ||  ( chess_in[x][y] >= 'j' &&  chess_in[x][y] <= 'k')      )
            {
                printf("%s",basic_word[ 28 - record_abs ] );                            //  打印如“红: 车一平二”的    二
                fprintf(out,"%s",basic_word[ 28 - record_abs ] );
            }   
            else
            {
                printf("%s",basic_word[ 19 + ( y + y_offset ) ] );
                fprintf(out,"%s",basic_word[ 19 + ( y + y_offset ) ] );
            }
        }
    }       
    else
    {
        printf("蓝: ");                                                                 //  蓝方同理，参见上面
        fprintf(out,"蓝: ");
        printf("%s",basic_word[chess_in[x][y]-'a'] );
        fprintf(out,"%s",basic_word[chess_in[x][y]-'a'] );
        printf("%d",y + 1 );
        fprintf(out,"%d",y + 1 );
        if ( x_offset == 0 )
        {
            printf("平%d", y + y_offset + 1 );
            fprintf(out,"平%d", y + y_offset + 1 );
        }    
        else
        {
            if ( x_offset > 0 )
            {
                printf("进");
                fprintf(out,"进");
            }
            else
            {
                printf("退");
                fprintf(out,"退");
            }      
            if (        ( chess_in[x][y] >= 'b' &&  chess_in[x][y] <= 'e') 
                    ||  ( chess_in[x][y] >= 'j' &&  chess_in[x][y] <= 'k')      )
            {
                printf("%d",  record_abs );
                fprintf(out,"%d",  record_abs );
            }    
            else
            {
                printf("%d", y_offset + y + 1 );
                fprintf(out,"%d", y_offset + y + 1 );
            }  
        }  
    }
    printf("\n");
    fprintf(out,"\n");
    return 0;
}

int go()                                                    //  可以移动后进行移动操作
{
    int temp = 0;                                           //  纪录棋子移动目的地的信息 
    step++;
    pu();                                                   //  调用记谱函数
    is_win();                                               //  判断移动后是否结束游戏
    if ( chess_in[x+x_offset][y+y_offset] != 'a' )          //  棋子移动目的地不是空格
        temp = chess_in[x+x_offset][y+y_offset];
    chess_in[x+x_offset][y+y_offset] = chess_in[x][y];      //  移动到目的地
    chess_in[x][y] = 'a';                                   //  原来棋子所在地置空
    if (temp != 0 && win == 0 )                             //  若目的地为敌方切还未结束则打印敌方被吃的子
        printf("\n%s被吃了\n",basic_word[temp-'a'] );
    show();                                                 //  展示移动后的棋盘
    printf("\n\n\n");
    colour[x][y] = 0;                                       //  移动过后对应格子上的棋子的颜色也要更新
    colour[x+x_offset][y+y_offset] = turn;
    turn = !turn;                                           //  回合轮转
    return 0;
}

int name_zu()                                               //  判断命令是否符合 卒或者兵 的移动规则
{
    if (   ( colour[x][y] == 1 && !( x_offset == 0 || x_offset == 1    )     )    // 兵不能往下走 x:-1 or 0
        || ( colour[x][y] == 0 && !( x_offset == 0 || x_offset == -1   )     )    // 卒不能往上走 x:+1 or 0
        || ( y > 1 && y < -1 				   							     )    // 不能走大于一格
        || ( (x == 3 || x == 4 ) && ( x_offset != 1  ) && colour[x][y] == 1  )	  // 未过河,卒只能向x-方向走一步
        || ( (x == 5 || x == 6 ) && ( x_offset != -1 ) && colour[x][y] == 0  )   )// 未过河,兵只能向x+方向走一步
        return -1;
    else
        go();                                                                     //  合法，移动

    return 0;
}

int i_touch(int n)                                                                //  判断直线型棋子一路碰到多少棋子
{
    int touch = 0, loop, i;
    if ( x_offset == 0 )                                                          //  向列走
    {
        loop = abs(y_offset);
        if ( y_offset > 0 )	                                                      //  列的正向
        {
            for (i = 1; i <= loop; ++i)
                if ( chess_in[x][ y + i ] != 'a' )
                    touch++;
        }
        else                                                                      //  列的负向
            for (i = 1; i <= loop; ++i)
                if ( chess_in[x][ y - i ] != 'a' )
                    touch++;
    }
    else                                                                          //  向行走
    {
        loop = abs(x_offset);
        if ( x_offset < 0 )                                                       //  行的正向
        {
            for (i = 1; i <= loop; ++i)
                if ( chess_in[ x - i ][y] != 'a' )
                    touch++;
        }
        else                                                                      //  列的负向
            for (i = 1; i <= loop; ++i)
                if ( chess_in[ x + i ][y] != 'a' )
                    touch++;
    }
    
    if ( n == 3 )                                                                 //  用于帅将的对射
    {
        if ( touch == 1 )                                                         //  mark for update， maybe
            return 1;
        else
            return 0;
    }   
            

    if ( ( touch == n && chess_in[ x + x_offset ][ y + y_offset ] != 'a' ) || touch == 0 )  //  碰到的数目符合车炮特点，且不为空格，则可行
        go();
    return 0;
}

int name_pao()                        //  是否炮的规则处理
{
    i_touch(2);
    return 0;
}
int name_ju()                         //  是否车的规则处理
{
    i_touch(1);
    return 0;
}
int name_ma()                          //  是否马的规则
{
    if( 	( y_offset == 2  && chess_in[x][ y + 1 ] == 'a' && ( x_offset == 1 || x_offset == -1) )	//别马脚，四个方位
       ||	( y_offset == -2 && chess_in[x][ y - 1 ] == 'a' && ( x_offset == 1 || x_offset == -1) )
       ||	( x_offset == 2  && chess_in[ x + 1 ][y] == 'a' && ( y_offset == 1 || y_offset == -1) )
       ||	( x_offset == -2 && chess_in[ x - 1 ][y] == 'a' && ( y_offset == 1 || y_offset == -1) )		)
       go();
    return 0;
}
int name_xiang()                        //  是否象相的规则处理
{
    if(  (	 ( x_offset == 2  && y_offset == -2 && chess_in[ x + 1 ][ y - 1 ] == 'a'  )	//别象脚
         ||  ( x_offset == -2 && y_offset == 2  && chess_in[ x - 1 ][ y + 1 ] == 'a'  )
         ||  ( x_offset == -2  && y_offset == -2 && chess_in[ x - 1 ][ y - 1 ] == 'a' )
         ||  ( x_offset == 2  && y_offset == 2  && chess_in[ x + 1 ][ y + 1 ] == 'a'  )	    )
         &&	 (	        ( x <= 4 && x + x_offset <= 4	)	//不能过河
                ||		( x >= 5 && x + x_offset >= 5	)	)									)
        go();
    return 0;
}
int name_shi()
{
    if(		(	( x_offset == 1 || x_offset == -1 ) && ( y_offset == 1 || y_offset == -1 )	)		 //走斜线
       &&	(	( x <= 2 && x + x_offset <= 2) || ( x >= 7 && x + x_offset >= 7 ) 	 		)		 //x.area，不能出界
       &&	(	( y >= 3 && y <= 5 ) && ( y + y_offset >= 3 && y + y_offset <= 5 ) 			)		)//y.area
        go();
    return 0;
}
int name_jiang()                         //  是否将帅的规则处理
{
    
    if(  (	(   (	( x_offset == 1 || x_offset == -1 ) && ( y_offset == 0 )	 	)			//走一格
         ||	(	( y_offset == 1 || y_offset == -1 ) && ( x_offset == 0 )	 		)		)
         &&	(	( x <= 2 && x + x_offset <= 2) || ( x >= 7 && x + x_offset >= 7  ) 	) 			//x.area
         &&	(	( y >= 3 && y <= 5 ) && ( y + y_offset >= 3 && y + y_offset <= 5 ) 	)		)   //y.area
         || (   ( chess_in[ x + x_offset ][ y + y_offset ] == 'k' ) &&                          //  是否将的射帅规则处理
                  chess_in[x][y] != 'k' && i_touch(3)                               )           //  都要调用碰到多少个棋子函数
         || (   ( chess_in[ x + x_offset ][ y + y_offset ] == 'j' ) &&                          //  是否帅的射将规则处理  
                  chess_in[x][y] != 'j' && i_touch(3)                               )	    )                       
        go();
    return 0;
}

int moves()                              //  移动的总体框架程序
{
    if (move_is_ok())                    //  调用是否可以移动函数进行判断，然后调用各个具体棋子处理函数
    {
        if 		(chess_in[x][y] == 'b' || chess_in[x][y] == 'c')   //  字母代表的是  兵卒
            return name_zu();
        else if (chess_in[x][y] == 'd')                            //  字母代表的是  炮
            return name_pao();
        else if (chess_in[x][y] == 'e')                            //  字母代表的是  车
            return name_ju();
        else if (chess_in[x][y] == 'f')                            //  字母代表的是  马
            return name_ma();
        else if (chess_in[x][y] == 'g' || chess_in[x][y] == 'h' )  //  字母代表的是  相象
            return name_xiang();
        else if (chess_in[x][y] == 'i')                            //  字母代表的是  士
            return name_shi();
        else if (chess_in[x][y] == 'j' || chess_in[x][y] == 'k')   //  字母代表的是  将帅
            return name_jiang();
    }
    return 0;
}


int set_shuxing(int n )             //  给初始棋盘的棋子做上颜色标号
{
    for ( j = 0; j < 9; ++j)
        if ( n < 5 && chess_in[n][j] != 'a' )       //  字母代表的是  a 表示空格，不着色
            colour[n][j] = 1;
    return 0;
}

int read_chess_in()                 //  从文件内读入棋盘信息
{
    FILE *in;                                                           //  打开文件
    in = fopen("chess.in","r");
    for ( i = 0; i < 11; ++i)                                           //  棋盘10行加楚河汉界11
    {
        fscanf(in, "%s",chess_in[i]);
        set_shuxing(i);				                                    //  读取数据时，对棋子进行色彩标记	
    }
    fclose(in);                                                         //  关闭文件
    return 0;
}

int get_command()            //  从键盘上输入命令到程序，进行移动棋子
{                            //  注意： 从  0行 0列 开始计数
    int xx,yy;               //  目标位置的坐标
    scanf("%d",&x);          //  要移动棋子的       行数  可输入0-9 共10行
    scanf("%d",&y);          //  要移动棋子的       列数  可输入0-8 共9行
    scanf("%d",&xx);         //  要移动棋子目的地的  行数  可输入0-9 共10行
    scanf("%d",&yy);         //  要移动棋子目的地的  列数  可输入0-8 共10行
    x_offset = xx - x;       //  计算 行偏移量
    y_offset = yy - y;       //  计算 列偏移量
    return 0;
}

int start()                  //  读完数据，开始下棋并记谱
{
    while(win == 0)          //  没人赢就不结束
    {
        get_command();       //  调用 获取移动命令 的函数
        moves();             //  调用 移动棋子    的函数
    }
    return 0;
}

int read_basic_word()       //  读取关键汉字，如卒兵等，用字符串处理，可以实现汉子的控制
{
    FILE *basic_word_in;    //  读取文件需要的指针
    basic_word_in = fopen("load_word.in","r");   //  打开文件
    for ( i = 0; i < 28; ++i)                                                   //  文件共28个汉字或字符
    {
        fscanf(basic_word_in,"%s",basic_word[i]);                               //  读取
    }
    fclose(basic_word_in);                                                      //  关闭文件
    return 0;
}

int main()                  //  主函数
{
    read_basic_word();      //  调用 读关键汉字   函数
    read_chess_in();        //  调用 读取初始棋盘 函数
    show();                 //  调用 展示初始期盼 函数
    out = fopen("pu.out","w");   //  创建 保存棋谱 的文件
    start();                //  调用 开始下棋    函数
    fclose(out);            //  结束时关闭 写谱 文件
    return 0;
}
