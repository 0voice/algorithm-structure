/*
 * 冒泡排序算法
 * create by JackChen
 */


#include<stdio.h>

void swap(int *a,int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

void bubbleSort(int *a,int length)
{
	int i,j;
	for(i=0;i<length;i++){
		for(j=i+1;j<length;j++){
			if(a[i]>a[j]){
				swap(&a[i],&a[j]);
			}
		}
	}
}

void arrayTraverse(int *a,int length)
{
	int i;
	for(i=0;i<length;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}


void main()
{
//	int a=1,b=2;
//	printf("交换之前a=%d,b=%d\n",a,b);
//	swap(&a,&b);
//	printf("交换之后a=%d,b=%d\n",a,b);

	int a[5]={2,5,1,3,4};
	bubbleSort(a,5);
	arrayTraverse(a,5);
}


