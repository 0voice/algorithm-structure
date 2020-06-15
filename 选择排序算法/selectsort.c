/*
 * 选择排序算法
 * create by JackChen
 */


#include<stdio.h>
#include<stdlib.h>

void selectsort(int arr[],int nlenght)
{
	
	int i,j;
	int min;
	for(i = 0;i<nlenght-1;i++)
	{
		min = i;
		for(j = i+1;j<nlenght;j++)
		{
			if(arr[j]<arr[min])
			{
				min  =j;	
			}
		}
	
		if(i!=min)
		{
			arr[i] = arr[i]^arr[min];
			arr[min] = arr[i]^arr[min];
			arr[i] = arr[i]^arr[min];
		}	
	}
		
}

void print(int arr[], int nlenght)
{
	int i;
	for(i = 0;i<nlenght;i++)
	{
		printf("%d   ",arr[i]);	
	}
	
	
}

int main()
{
	int arr[] = {8,3,5,1,4};
	selectsort(arr,sizeof(arr)/sizeof(arr[0]));
	print(arr,sizeof(arr)/sizeof(arr[0]));
	printf("\n");	
return 0;
}
