#pragma once

/*
*»ùÊýÅÅÐò
*/


int GetMaxDigit(int* a,int size)
{
	int max = 10;
	int digit = 1;
	for (int i = 0; i < size; ++i)
	{
		while (a[i]>=max)
		{
			digit++;
			max *= 10;
		}
	}
	return digit;
}

void DigitSort(int* a, int size)
{
	int* tmp = new int[size];
	int* b = new int[size];
	
	for (int i = 0; i < size; ++i)
	{
		b[i] = a[i];
	}
	
	int digit = GetMaxDigit(a, 10);
	while (digit--)
	{
		for (int i = 0; i < size; ++i)
		{
			tmp[i] = b[i] % 10;
			b[i] /= 10;
		}

		
		for (int i = 0; i < size; ++i)
		{
			for (int j = i; j < size; ++j)
			{
				if (tmp[i]>tmp[j])
				{
					swap(tmp[i], tmp[j]);
					swap(b[i], b[j]);
					swap(a[i], a[j]);
				}
			}
		}
	}
	
	delete[] tmp;
}
