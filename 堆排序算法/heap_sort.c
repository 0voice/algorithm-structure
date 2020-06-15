/**
* ∂—≈≈–ÚÀ„∑®
**/

#include<stdio.h>
void swap(int *a,int *b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
void adjust_down(int arr[],int root,int size)
{
	int parent=root;
	int left=root*2+1;
	int right=left+1;
	while(left<size){
		int max=left;
		if(right<size && arr[right]>arr[max]){
			max=right;
		}
		if(arr[max]>arr[parent]){
			swap(&arr[max],&arr[parent]);
			parent=max;
			left=parent*2+1;
			right=left+1;
		}
		else{
			break;
		}
	}
}
//make min heap
void heap_sort(int arr[],int size)
{
	int begin=0;
	for(begin=size/2-1;begin>=0;--begin){
		adjust_down(arr,begin,size);
	}
	int end=size-1;
	while(end>0){
		swap(&arr[0],&arr[end]);
		adjust_down(arr,0,end);
		--end;
	}
}
int main()
{
	int arr[10]={3,7,1,4,2,8,5,0,9,6};
	heap_sort(arr,10);
	int i=0;
	for(;i<10;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}