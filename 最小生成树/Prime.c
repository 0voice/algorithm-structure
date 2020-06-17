
#include<stdio.h>
#include<stdlib.h>
#define MaxCost 600.
#define MaxEdge 50
#define MinLen 20
#define Cost 5 
float Prime(float graph[][MaxEdge],int p)
{
	float mincost[MinLen]; 
	int minmid,i,j,m; 
	float sum = 0;
	int mst[MinLen]; 

	mincost[1] = 0.; 
	mst[0] =  1;
	for(i = 2;i <= p;i++)
	{
		mst[i] = 1; 
		mincost[i] = graph[1][i];
		
	}
	for(i = 2; i <= p;i++)
	{
		 float min = MaxCost;
		 for(j = 2;j <= p;j++)
		 {
		 	if(mincost[j] < min&&mincost[j] != 0.)
		 	{
		 		min = mincost[j];  
		 		minmid = j;
			 }
		 }
		 sum += min;
		 mincost[minmid] = 0.;
		 printf("%d---->%d\n",mst[minmid],minmid);
		 for(j = 2;j <= p;j++) 
		 {
		 	if(graph[minmid][j] < mincost[j])
			 {
			 	mincost[j] = graph[minmid][j];
			 	mst[j] = minmid;
			  } 
		 }
	}
	return sum;
 } 
int main()
{
	printf("请输入点的个数与边的条数\n");
	int p,e,i,j;
	float graph[MaxEdge][MaxEdge];
	int p1,p2; 
	float val,re;
	scanf("%d%d",&p,&e);
	for(i = 0;i < MaxEdge;i++) 
	{
		for(j = 0;j < MaxEdge;j++)
		{
			graph[i][j] = MaxCost;
		}
	}
	for(i = 1; i <= e;i++)
	{
		
		printf("输入两点与其间的权值\n");
		scanf("%d%d%f",&p1,&p2,&val);
		graph[p1][p2] = val;
		graph[p2][p1] = val;	
	}
	re = Prime(graph,p); 
	printf("result = %0.2f",re);
}
