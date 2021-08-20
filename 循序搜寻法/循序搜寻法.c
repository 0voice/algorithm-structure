#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
int search(int[]);
int partition(int[], int, int);
void quicksort(int[], int, int);
int main(void) {
	int number[MAX+1] = {0};
	int i, find;
	srand(time(NULL));
	for(i = 1; i <= MAX; i++)
		number[i] = rand() % 100;
	quicksort(number, 1, MAX);
	printf("数列：");
	for(i = 1; i <= MAX; i++)
		printf("%d ", number[i]);
	printf("\n输入搜寻值：");
	scanf("%d", &number[0]);
	if(find = search(number))
		printf("\n找到数值于索引 %d ", find);
	else
	printf("\n找不到数值");
	printf("\n");
	return 0;
}

int search(int number[]) {
	int i, k;
	k = number[0];
	i = MAX;
	while(number[i] != k)
		i--;
	return i;
}

int partition(int number[], int left, int right) {
	int i, j, s;
	s = number[right];
	i = left - 1;
	for(j = left; j < right; j++) {
		if(number[j] <= s) {
			i++;
			SWAP(number[i], number[j]);
			}
	}
	SWAP(number[i+1], number[right]);
	return i+1;
}

void quicksort(int number[], int left, int right) {
	int q;
	if(left < right) {
		q = partition(number, left, right);
		quicksort(number, left, q-1);
		quicksort(number, q+1, right);
	}
}
