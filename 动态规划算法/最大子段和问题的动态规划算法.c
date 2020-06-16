//最大子段和问题的动态规划算法  
#include <stdio.h>  

int MaxSum(int n, int *a);

int main()
{
	int a[] = { -2, 11, -4, 13, -5, -2 };
	for (int i = 0; i<6; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("数组a的最大连续子段和为:%d\n", MaxSum(6, a));
	return 0;
}

int MaxSum(int n, int *a)
{
	int sum = 0, b = 0;
	for (int i = 1; i <= n; i++)
	{
		if (b>0)
		{
			b += a[i];
		}
		else
		{
			b = a[i];
		}
		if (b>sum)
		{
			sum = b;
		}
	}
	return sum;
}