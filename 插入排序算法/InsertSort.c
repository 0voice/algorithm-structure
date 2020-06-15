/*
 * 插入排序算法
 * create by JackChen
 */

#include<stdio.h>
#include<stdlib.h>

void insertsort(int arr[],int nlenght)
{
	int i,j;
	int ptemp;
	for(i = 0;i<nlenght;i++)
	{
		j = i-1;
		ptemp = arr[i];
		while(arr[j]>ptemp   && j>=0)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = ptemp;
		
	}
	
	
}

void print(int arr[], int nlenght)
{
	int i;
	for(i = 0;i<nlenght;i++)
	{
	printf("%d  ",arr[i]);	
	}
	
}
int main()
{
	
	int arr[] = {6,1,2,8,4,9};

	insertsort(arr,sizeof(arr)/sizeof(arr[0]));
	print(arr,sizeof(arr)/sizeof(arr[0]));
	
	
printf("\n");	
	return 0;
}
