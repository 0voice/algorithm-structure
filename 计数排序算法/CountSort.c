#pragma once

/*
*¼ÆÊıÅÅĞò
*/

void CountSort(int* a, int size)
{	
	int max = a[0];
	int min = a[0];
	for (int i = 1; i < size; ++i)
	{
		if (max < a[i])
		{
			max = a[i];
		}
		if (min>a[i])
		{
			min = a[i];
		}
	}

	int range = max - min + 1;
	int* countArray = new int[range];
	memset(countArray,0,range*sizeof(int));

	for (int i = 0; i < size; ++i)
	{
		countArray[a[i] - min]++;
	}

	int index = 0;
	for (int i = 0; i < size; ++i)
	{
		while (countArray[i]-- > 0)
		{
			a[index++] = i;
		}
	}
	delete[] countArray;
}

