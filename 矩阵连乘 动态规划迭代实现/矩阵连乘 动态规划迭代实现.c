//矩阵连乘 动态规划迭代实现  

#include <stdio.h>  
const int L = 7;
int MatrixChain(int n, int **m, int **s, int *p);
void Traceback(int i, int j, int **s);
int main()
{
	int p[] = { 30, 35, 15, 5, 10, 20, 25 };
	int **s = (int**)malloc(L*sizeof(int*));
	int **m = (int**)malloc(L*sizeof(int*));
	for (int i = 0; i < L; i++){
		s[i] = (int*)malloc(L*sizeof(int));
		m[i] = (int*)malloc(L*sizeof(int));
	}
	printf("矩阵的最少计算次数为：%d\n", MatrixChain(6, m, s, p));
	printf("矩阵最优计算次序为：\n");
	Traceback(1, 6, s);
	return 0;
}
int MatrixChain(int n, int **m, int **s, int *p)
{
	for (int i = 1; i <= n; i++)
	{
		m[i][i] = 0;
	}
	for (int r = 2; r <= n; r++)
	{
		for (int i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k<j; k++)
			{
				
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t<m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
	return m[1][L - 1];
}
void Traceback(int i, int j, int **s)
{
	if (i == j) return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	printf("Multiply A%d,%d", i, s[i][j]);
	printf(" and A%d,%d\n", (s[i][j] + 1), j);
}