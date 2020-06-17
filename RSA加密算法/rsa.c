/*
*RSA加解密算法
*/

#include <stdio.h>
#include <math.h>


#define P	5	
#define	Q	7

#define N	(P*Q)	
#define Z	((P - 1)*(Q - 1))

#define E	5		
#define D	5		



int main(void)
{
	int i;
	int TrsMsg[4] = {12, 15, 22, 5};
	long en[4], de[4];
	int SecCode[4], DeMsg[4];

	printf("下面是一个RSA加解密算法的简单演示:\n");
	printf("\t Copyright(C) Long.Luo.\n\n");
	printf("报文\t加密\t   加密后密文\n");

	for (i=0; i<4; i++)
	{
		en[i] = (int)pow(TrsMsg[i], E);
		SecCode[i] = en[i] % N;

		printf("%d\t%d\t\t%d\n", TrsMsg[i], en[i], SecCode[i]);
	}

	printf("\n原始报文\t密文\t加密\t\t解密报文\n");
	for (i=0; i<4; i++)
	{
		de[i] = pow(SecCode[i], D);
		DeMsg[i] = de[i] % N;

		printf("%d\t\t%d\t%d\t\t%d\n", TrsMsg[i], SecCode[i], de[i], DeMsg[i]);
	}

	getchar();
  
  return 0;
}


