// 矩阵连乘 备忘录递归实现  

#include <stdio.h>  
const int L = 7;
int LookupChain(int i, int j, int **m, int **s, int *p);
int MemoizedMatrixChain(int n, int **m, int **s, int *p);
void Traceback(int i, int j, int **s);/
int main()
{
	int p[] = { 30, 35, 15, 5, 10, 20, 25 };
	int **s = (int**)malloc(L*sizeof(int*));
	int **m = (int**)malloc(L*sizeof(int*));
	for (int i = 0; i < L; i++){
		s[i] = (int*)malloc(L*sizeof(int));
		m[i] = (int*)malloc(L*sizeof(int));
	}
	printf("矩阵的最少计算次数为：%d\n", MemoizedMatrixChain(6, m, s, p));
	printf("矩阵最优计算次序为：\n");
	Traceback(1, 6, s);
	return 0;
}
int MemoizedMatrixChain(int n, int **m, int **s, int *p)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			m[i][j] = 0;
		}
	}
	return LookupChain(1, n, m, s, p);
}
int LookupChain(int i, int j, int **m, int **s, int *p)
{
	if (m[i][j]>0)
	{
		return m[i][j];
	}
	if (i == j)
	{
		return 0;
	}
	int u = LookupChain(i, i, m, s, p) + LookupChain(i + 1, j, m, s, p) + p[i - 1] * p[i] * p[j];
	s[i][j] = i;
	for (int k = i + 1; k<j; k++)
	{
		int t = LookupChain(i, k, m, s, p) + LookupChain(k + 1, j, m, s, p) + p[i - 1] * p[k] * p[j];
		if (t<u)
		{
			u = t;
			s[i][j] = k;
		}
	}
	m[i][j] = u;
	return u;
}
void Traceback(int i, int j, int **s)
{
	if (i == j) return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	printf("Multiply A%d,%d", i, s[i][j]);
	printf(" and A%d,%d\n", (s[i][j] + 1), j);
}