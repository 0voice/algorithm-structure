//ID3算法是数据挖掘算法之一，以下是ID3算法的示例程序的全部源代码

#include<stdio.h>

#include<conio.h>

#include<malloc.h>

#include<math.h>

#include<string.h>

 

#define NOTHING 10

//天气值域

#define SUNNY    11

#define VOERCAST    12

#define RAIN 13

//风值域

#define TRUE 1

#define FALSE     0

//类别属性值域

#define CAN_PLAY     14

#define NOT_PLAY     15

//非类别属性值域

#define OUTLOOK      16

#define TEMPERATURE     17

#define HUMIDITY     18

#define WINDY    19

//将温度分三个类

#define HIGH_TEMPERATURE  8

#define MID_TEMPERATURE   7

#define COLD_TEMPERATURE  6

//将湿度分两个类

#define HIGH_HUMIDITY         75

#define NORMAL_HUMIDITY   74

#define TRAINING_NUMBER   14

//训练数据集结构

struct TRAINING

{

int outLook;

int temperature;

int humidity;

int windy;

int play;

struct TRAINING *next;

};

//温度和湿度增益结构

struct TEMPER_HUMID_GAIN

{

int value;

int playCount;

int c;

};

//非类属性集结构

struct SET

{

int item;

struct SET *next;

};

//决策树结构

struct TREE

{

int attribute;

struct TREE *left;

struct TREE *mid;

struct TREE *right;

};

struct TRAINING *trainHead;

struct SET *noClassSetHead;

struct TREE *treeT;

//天气数据库的训练数据

struct TRAINING trainingSet[TRAINING_NUMBER]=

{

{SUNNY  ,85,85,FALSE,NOT_PLAY,NULL},

{SUNNY  ,80,90,TRUE ,NOT_PLAY,NULL},

{VOERCAST,83,78,FALSE,CAN_PLAY,NULL},

{RAIN   ,70,96,FALSE,CAN_PLAY,NULL},

{RAIN   ,68,80,FALSE,CAN_PLAY,NULL},

{RAIN   ,65,70,TRUE ,NOT_PLAY,NULL},

{VOERCAST,64,65,TRUE ,CAN_PLAY,NULL},

{SUNNY  ,72,95,FALSE,NOT_PLAY,NULL},

{SUNNY  ,69,70,FALSE,CAN_PLAY,NULL},

{RAIN   ,75,80,FALSE,CAN_PLAY,NULL},

{SUNNY  ,75,70,TRUE ,CAN_PLAY,NULL},

{VOERCAST,72,90,TRUE ,CAN_PLAY,NULL},

{VOERCAST,81,75,FALSE,CAN_PLAY,NULL},

{RAIN   ,71,80,TRUE ,NOT_PLAY,NULL}

};

//非类集合和类集合

int noClassSet[4]={OUTLOOK,TEMPERATURE,HUMIDITY,WINDY};

int classSet[2]={CAN_PLAY,NOT_PLAY};

 

//函数功能：计算以2为底的对数

double Log2(double x)

{

if(x<=0)

return 0.0;

else

return (double)log10(x)/log10(2);

}

//函数功能：获取信息量

double I(double p1,double p2)

{

return -(p1*Log2(p1)+p2*Log2(p2));

}

//函数功能：计算训练集的信息量

double Information(struct TRAINING *head)

{

double p1,p2;

int c=0;

int canPlay=0;

int notPlay=0;

struct TRAINING *p;

p=head->next;

while(p)

{

c++;

if(p->play==CAN_PLAY)

canPlay++;

else

notPlay++;

p=p->next;

}

p1=(double)canPlay/c;

p2=(double)notPlay/c;

return I(p1,p2);

}

 

//函数功能：判断训练子集是否全部同一类

int ClassAllSame(struct TRAINING *head)

{

struct TRAINING *p;

int same;

p=head->next;

same=p->play;

while(p)

{

if(p->play!=same)

return 0;

p=p->next;

}

return 1;

}

//函数功能：判断训练子集是否为空

int ClassIsEmpty(struct TRAINING *head)

{

struct TRAINING *p;

int c=1;

p=head->next;

while(p)

{

c--;

if(!c)

break;

p=p->next;

}

return c;

}

//函数功能：判断非类属性是否为空

int ClassSetIsEmpty(struct SET *head)

{

struct SET *p;

int c=1;

p=head->next;

while(p)

{

c--;

if(!c)

break;

p=p->next;

}

return c;

}

//函数功能：从非类属性集中删除值为value的非类属性

void DeleteClassSet(int value,struct SET *head)

{

struct SET *p,*q;

q=head;

p=head->next;

while((p)&&(p->item!=value))

{

q=p;

p=p->next;

}

q->next=p->next;

free(p);

}

 

//函数功能：根据Gain值取得Gain最大值所对应的非类属性。

int GetMaxGainClass(int c,double *p,struct SET *head)

{

struct SET *t;

double max,*s;

int i=0,j=0;

s=p;

max=*(s);

t=head;

for(i=0;i<c;i++)

{

if(*(s+i)>max)

{

max=*(s+i);

j=i;

}

}

for(i=0;i<=j;i++)

t=t->next;

return t->item;

}

//函数功能：从训练集中以非类属性“outLook”获取子集

struct TRAINING *GetSubSet(int attr,struct TRAINING *head)

{

struct TRAINING *p,*q,*tempHead,*t;

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

tempHead=p;

p->next=NULL;

q=p;

t=head->next;

switch(attr)

{

case SUNNY:

while(t)

{

if(t->outLook==SUNNY)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

case VOERCAST:

while(t)

{

if(t->outLook==VOERCAST)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

case RAIN:

while(t)

{

if(t->outLook==RAIN)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

}

return NULL;

}

//函数功能：从训练集中以非类属性“temperature”获取子集

struct TRAINING *GetSubSet1(int attr,struct TRAINING *head)

{

struct TRAINING *p,*q,*tempHead,*t;

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

tempHead=p;

q=p;

t=head->next;

switch(attr)

{

case HIGH_TEMPERATURE:

while(t)

{

if(t->temperature/10==HIGH_TEMPERATURE)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

case MID_TEMPERATURE:

while(t)

{

if(t->temperature/10==MID_TEMPERATURE)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

case COLD_TEMPERATURE:

while(t)

{

if(t->temperature/10==COLD_TEMPERATURE)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

}

return NULL;

}

//函数功能：从训练集中以非类属性“humidity”获取子集

struct TRAINING *GetSubSet2(int attr,struct TRAINING *head)

{

struct TRAINING *p,*q,*tempHead,*t;

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

tempHead=p;

q=p;

t=head->next;

switch(attr)

{

case HIGH_HUMIDITY:

while(t)

{

if(t->humidity>=HIGH_HUMIDITY)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

case NORMAL_HUMIDITY:

while(t)

{

if(t->humidity<=NORMAL_HUMIDITY)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

}

return NULL;

}

//函数功能：从训练集中以非类属性“windy”获取子集

struct TRAINING *GetSubSet3(int attr,struct TRAINING *head)

{

struct TRAINING *p,*q,*tempHead,*t;

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

tempHead=p;

q=p;

t=head->next;

switch(attr)

{

case TRUE:

while(t)

{

if(t->windy==TRUE)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

case FALSE:

while(t)

{

if(t->windy==FALSE)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=t->outLook;

p->temperature=t->temperature;

p->humidity=t->humidity;

p->windy=t->windy;

p->play=t->play;

q->next=p;

q=q->next;

}

t=t->next;

}

return tempHead;

}

return NULL;

}

//函数功能：建立非类属性集

struct SET *CreateNoClassSet(int noClass[])

{

int i;

struct SET *head,*p,*q;

p=(struct SET *)malloc(sizeof(struct SET));

memset(p,0,sizeof(struct SET));

head=p;

q=p;

for(i=0;i<4;i++)

{

p=(struct SET *)malloc(sizeof(struct SET));

memset(p,0,sizeof(struct SET));

p->item=noClass[i];

q->next=p;

q=q->next;

}

return head;

}

//函数功能：建立训练数据集

struct TRAINING *CreateTrainingLink(struct TRAINING set[])

{

struct TRAINING *head,*p,*q;

int i;

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

head=p;

p->next=NULL;

q=p;

for(i=0;i<TRAINING_NUMBER;i++)

{

p=(struct TRAINING *)malloc(sizeof(struct TRAINING));

memset(p,0,sizeof(struct TRAINING));

p->outLook=set[i].outLook;

p->temperature=set[i].temperature;

p->humidity=set[i].humidity;

p->windy=set[i].windy;

p->play=set[i].play;

p->next=NULL;

q->next=p;

q=q->next;

}

return head;

}

//函数功能：计算加权平均值

double InformationAttr(int attribute,struct TRAINING *head)

{

struct TRAINING *p;

struct TEMPER_HUMID_GAIN tGain[3];

struct TEMPER_HUMID_GAIN mGain[2];

int c=0;

int i=0,j=0;

int sunny=0,overcast=0,rain=0;

int sPlay=0,oPlay=0,rPlay=0;

int wind=0,windPlay=0;

int noWind=0,noWindPlay=0;

double p1=0,p2=0,p3=0;

double i1=0,i2=0,i3=0;

p=head->next;

switch(attribute)

{

case OUTLOOK:

while(p)

{

c++;

if(p->outLook==SUNNY)

{

sunny++;//晴天总数

if(p->play==CAN_PLAY)

sPlay++;//是晴天时且可以打球的天数

}

if(p->outLook==VOERCAST)

{

overcast++;

if(p->play==CAN_PLAY)

oPlay++;

}

if(p->outLook==RAIN)

{

rain++;

if(p->play==CAN_PLAY)

rPlay++;

}

p=p->next;

}

p1=(double)sunny/c;

p2=(double)overcast/c;

p3=(double)rain/c;

if(sunny)

i1=I((double)sPlay/sunny,

(double)(sunny-sPlay)/sunny);

if(overcast)

i2=I((double)oPlay/overcast,

(double)(overcast-oPlay)/overcast);

if(rain)

i3=I((double)rPlay/rain,

(double)(rain-rPlay)/rain);

return p1*i1+p2*i2+p3*i3;

case TEMPERATURE:

for(i=0;i<3;i++)

{

tGain[i].c=0;

tGain[i].playCount=0;

if(i==0)

tGain[i].value=HIGH_TEMPERATURE;

else if(i==1)

tGain[i].value=MID_TEMPERATURE;

else

tGain[i].value=COLD_TEMPERATURE;

}

while(p)

{

c++;

if(p->temperature/10==HIGH_TEMPERATURE)

{

tGain[0].c++;

if(p->play==CAN_PLAY)

tGain[0].playCount++;

}

else if(p->temperature/10==MID_TEMPERATURE)

{

tGain[1].c++;

if(p->play==CAN_PLAY)

tGain[1].playCount++;

}

else if(p->temperature/10==COLD_TEMPERATURE)

{

tGain[2].c++;

if(p->play==CAN_PLAY)

tGain[2].playCount++;

}

p=p->next;

}

p1=(double)tGain[0].c/c;

p2=(double)tGain[1].c/c;

p3=(double)tGain[2].c/c;

if(tGain[0].c)

i1=I((double)tGain[0].playCount/tGain[0].c,

(double)(tGain[0].c-tGain[0].playCount)/tGain[0].c);

if(tGain[1].c)

i2=I((double)tGain[1].playCount/tGain[1].c,

(double)(tGain[1].c-tGain[1].playCount)/tGain[1].c);

if(tGain[2].c)

i3=I((double)tGain[2].playCount/tGain[2].c,

(double)(tGain[2].c-tGain[2].playCount)/tGain[2].c);

return p1*i1+p2*i2+p3*i3;

case HUMIDITY:

for(i=0;i<2;i++)

{

mGain[i].c=0;

mGain[i].playCount=0;

if(i==0)

mGain[i].value=HIGH_HUMIDITY;

else

mGain[i].value=NORMAL_HUMIDITY;

}

while(p)

{

c++;

if(p->humidity>=mGain[0].value)

{

mGain[0].c++;

if(p->play==CAN_PLAY)

mGain[0].playCount++;

}

else if(p->humidity<mGain[1].value)

{

mGain[1].c++;

if(p->play==CAN_PLAY)

mGain[1].playCount++;

}

p=p->next;

}

p1=(double)mGain[0].c/c;

p2=(double)mGain[1].c/c;

if(mGain[0].c)

i1=I((double)mGain[0].playCount/mGain[0].c,

(double)(mGain[0].c-mGain[0].playCount)/mGain[0].c);

if(mGain[1].c)

i2=I((double)mGain[1].playCount/mGain[1].c,

(double)(mGain[1].c-mGain[1].playCount)/mGain[1].c);

return p1*i1+p2*i2;

case WINDY:

while(p)

{

c++;

if(p->windy==TRUE)

{

wind++;

if(p->play==CAN_PLAY)

windPlay++;

}

if(p->windy==FALSE)

{

noWind++;

if(p->play==CAN_PLAY)

noWindPlay++;

}

p=p->next;

}

p1=(double)wind/c;

p2=(double)noWind/c;

if(wind)

i1=I((double)windPlay/wind,

(double)(wind-windPlay)/wind);

if(noWind)

i2=I((double)noWindPlay/noWind,

(double)(noWind-noWindPlay)/noWind);

return p1*i1+p2*i2;

}

return 0.0;

}

//函数功能：获取增益

double Gain(int attribute,struct TRAINING *head)

{

return Information(head)-InformationAttr(attribute,head);

}

 

//函数功能：排序

void Compositor(int len,int *p)

{

int i,j;

int temp;

for(i=0;i<len;i++)

for(j=i;j<len;j++)

{

if(*(p+j)<*(p+i))

{

temp=*(p+j);

*(p+j)=*(p+i);

*(p+i)=temp;

}

}

}

//函数功能：返回被删除的元素的个数

int DeleteTheSameElement(int len,int *p)

{

int i,j;

int c=0;

for(i=0;i<len-c;i++)

{

j=i+1;

if(*(p+i)==*(p+j))

{

for(;j<len-c;j++)

{

*(p+j)=*(p+j+1);

}

*(p+j)='\0';

c++;

i--;

}

}

return c;

}

//函数功能：用ID3算法建立一棵决策树

struct TREE *CreatTree(struct SET *classHead,int Class[],struct TRAINING *head)

{

struct TREE *root,*t1,*t2,*t3;

struct TRAINING *p,*sub1,*sub2,*sub3;

struct SET *r;

int i;

int classSetCount=0;

int count1=0,count2=0;

double *gainPoint;

root=(struct TREE *)malloc(sizeof(struct TREE));

memset(root,0,sizeof(struct TREE));

if(ClassIsEmpty(head))

{

root->attribute=NOTHING;

return root;

}

if(ClassAllSame(head))

{

root->attribute=head->next->play;

return root;

}

if(ClassSetIsEmpty(classHead))

{

p=head->next;

while(p)

{

if(p->play==Class[0])

count1++;

if(p->play==Class[1])

count2++;

}

if(count1>count2)

root->attribute=Class[0];

else

root->attribute=Class[1];

return root;

}

r=classHead->next;

while(r)

{

classSetCount++;

r=r->next;

}

gainPoint=(double *)malloc(classSetCount*sizeof(double));

memset(gainPoint,0,classSetCount*sizeof(double));

r=classHead->next;

for(i=0;i<classSetCount;i++)

{

*(gainPoint+i)=Gain(r->item,head);

printf("gainPoint=%f,item=%d\n",*(gainPoint+i),r->item);

r=r->next;

}

i=GetMaxGainClass(classSetCount,gainPoint,classHead);

DeleteClassSet(i,classHead);//从R(classHead)中减去{D}

printf("i=M\n",i);

switch(i)

{

case OUTLOOK:

root->attribute=OUTLOOK;

root->left=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->left,0,sizeof(struct TREE));

root->left->attribute=VOERCAST;

t1=root->left;

root->mid=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->mid,0,sizeof(struct TREE));

root->mid->attribute=SUNNY;

t2=root->mid;

root->right=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->right,0,sizeof(struct TREE));

root->right->attribute=RAIN;

t3=root->right;

sub1=GetSubSet(VOERCAST,head);

t1->left=CreatTree(classHead,Class,sub1);

sub2=GetSubSet(SUNNY,head);

t2->mid=CreatTree(classHead,Class,sub2);

sub3=GetSubSet(RAIN,head);

t3->right=CreatTree(classHead,Class,sub3);

break;

case TEMPERATURE:

root->attribute=TEMPERATURE;

root->left=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->left,0,sizeof(struct TREE));

root->left->attribute=HIGH_TEMPERATURE;

t1=root->left;

root->mid=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->mid,0,sizeof(struct TREE));

root->mid->attribute=MID_TEMPERATURE;

t2=root->mid;

root->right=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->right,0,sizeof(struct TREE));

root->right->attribute=COLD_TEMPERATURE;

t3=root->right;

break;

case HUMIDITY:

root->attribute=HUMIDITY;

root->left=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->left,0,sizeof(struct TREE));

root->left->attribute=HIGH_HUMIDITY;

t1=root->left;

root->mid=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->mid,0,sizeof(struct TREE));

root->mid->attribute=NORMAL_HUMIDITY;

t2=root->mid;

sub1=GetSubSet2(HIGH_HUMIDITY,head);

sub2=GetSubSet2(NORMAL_HUMIDITY,head);

t1->right=CreatTree(classHead,Class,sub1);

t2->right=CreatTree(classHead,Class,sub2);

break;

case WINDY:

root->attribute=WINDY;

root->left=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->left,0,sizeof(struct TREE));

root->left->attribute=TRUE;

t1=root->left;

root->mid=(struct TREE *)malloc(sizeof(struct TREE));

memset(root->mid,0,sizeof(struct TREE));

root->mid->attribute=FALSE;

t2=root->mid;

sub1=GetSubSet3(TRUE,head);

sub2=GetSubSet3(FALSE,head);

t1->left=CreatTree(classHead,Class,sub1);

t2->left=CreatTree(classHead,Class,sub2);

break;

default:

return NULL;

}

return root;

}

 

 

//函数功能：显示决策树

void DisplayTree(struct TREE *t)

{

struct TREE *p;

p=t;

if(p)

{

printf("tree=%d\n",p->attribute);

DisplayTree(p->left);

DisplayTree(p->mid);

DisplayTree(p->right);

}

}

int main()

{

 

trainHead=CreateTrainingLink(trainingSet);

noClassSetHead=CreateNoClassSet(noClassSet);

treeT=CreatTree(noClassSetHead,classSet,trainHead);

DisplayTree(treeT);

free(treeT);

free(noClassSetHead);

free(trainHead);

printf("\n按任意键退出");

getch();

return 0;

}
