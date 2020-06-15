/**
* ¿ìËÙÅÅĞòËã·¨
**/

#include<stdio.h>
void quick_sort(int arr[],int left,int right)
{
	if(left>=right){
		return;
	}
	int key=arr[left];
	int begin=left;
	int end=right;
	while(begin!=end){
		while(begin<end && arr[end]>=key){
			end--;
		}
		if(end>begin){
			arr[begin]=arr[end];
		}
		while(begin<end && arr[begin]<=key){
			begin++;
		}
		if(begin<end){
			arr[end]=arr[begin];
		}
	}
	arr[begin]=key;
	quick_sort(arr,left,begin-1);
	quick_sort(arr,begin+1,right);
}
int main()
{
	int arr[]={3,6,1,9,4,2,0,5,8,7};
	quick_sort(arr,0,9);
	int i=0;
	for(i=0;i<10;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}