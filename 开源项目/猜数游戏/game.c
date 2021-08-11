#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h> 
main(){
  FILE *fp;
  char a;
  int k=0,t=0,n,number,answer,maxnumber,mychoose1,mychoose2,standard;/*将当前时间设置成随机函数的种子，所以每次产生的数都不一样*/
  if ((fp=fopen("README2.txt","r+"))==NULL){
     printf("Cannot open file!\n");exit(0);}
  while((a=fgetc(fp))!=EOF)
     putchar(a);

    aa: printf("\n             菜单  \n1.开始   2.退出  \n");
     scanf("%d",&mychoose1);
     switch(mychoose1){
 case 1:  printf("    请选择难易程度\n1.简单  2.普通   3.困难   4.自定义\n");
     scanf("%d",&standard);
 switch(standard){
 	case 1:n=pow(10,2);break;
 	case 2:n=pow(10,3);break;
 	case 3:n=pow(10,4);break;
 	case 4:printf("给出的数最大可以是多少？\n0~%d");
 	       scanf("%d ",&maxnumber);
			while(maxnumber>0){
				maxnumber/=10;
				t++;
			} n=pow(10,t);break;
 }   
     srand( (unsigned)time( NULL ) );
     number=rand()%n;
  printf("猜猜看是哪个数字\n");
   do{
        scanf("%d",&answer);
        fprintf(fp,"%d\n",answer);
       if(answer>number){ 
            printf("猜大了,再来一次\n");
            fprintf(fp,"猜大了,再来一次\n");} 
        if(answer<number){ 
            printf("猜小了，再来一次\n");
            fprintf(fp,"猜小了,再来一次\n");} 
            k++;
    }while(answer!=number);
    printf("这次你只用了%d次就猜出了答案，你运气真好!\n",k);
    fprintf(fp,"这次你只用了%d次就猜出了答案，你运气真好!\n",k);
     printf("1.再来一次  2.退出");
     scanf("%d",&mychoose2);
     switch(mychoose2){
  	case 1:goto aa;break;
  	case 2:fclose(fp);break;
	 }break;
case 2:fclose(fp);break;}
}
