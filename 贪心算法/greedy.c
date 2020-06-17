/*
* 贪心算法
*/
#include<stdio.h>
void schedule(int m,int n,int *t){
	
	int i,j,k,max=0;
	int d[100],s[100][100],count[100];
	for(i=0;i<m;i++){
		d[i]=0;
		for(j=0;j<n;j++){
			s[i][j]=-1;
		}
	}
	
	for(i=0;i<m;i++){
		s[i][0]=i;
		d[i]=d[i]+t[i];
		count[i]=1;
	}
	
	for(i=m;i<n;i++){
		int min=d[0];
		k=0;
		for(j=1;j<m;j++){
			if(min>d[j]){
				min=d[j];
				k=j;
			}
		}
		s[k][count[k]]=i;
		count[k]=count[k]+1;
		d[k]=d[k]+t[i];	
	}
	
	for(i=0;i<m;i++){
		if(max<d[i]){
			max=d[i];
		}			
	}
	printf("完成所有任务需要的时间：%d\n",max);
	printf("各个机器执行的耗时一览：\n");
	for(i=0;i<m;i++){
		printf("%d:",i);
		for(j=0;j<n;j++){
			if(s[i][j]==-1){
				break;
			}
			printf("%d\t",t[s[i][j]]);
		}
		printf("\n");
	}
}
