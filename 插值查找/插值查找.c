#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//插值查找法 arr数组，length 数组长度，key 查找的关键字
//返回查找值的下标 ，没查找到 返回-1
int Interpolation_Search(int *arr, int length, int key)
{
	int low = 0;//低位下标
	int high = length-1;//高位下标
	int mid;//中间值下标
	while (low <= high)
	{
		mid = (high-low)*(key - arr[low]) / (arr[high] - arr[low]);//插值
		if (key < arr[mid])
		{
			high = mid - 1;
		}
		else if(key > arr[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}
int main(int argc, char *argv[])
{
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9};
	int index1 = Interpolation_Search(arr, 10, 5);
	int index2 = Interpolation_Search(arr, 10, 100);
	printf("index1 = %d，index2 = %d\n",index1,index2);
	return 0;
}
