#include <stdio.h>

void reverse(int *A, int n);

int main() {
	int table[10] = {1,2,3,4,5,6,7,8,9,10};

	printf("Original:\n");
	for (int i = 0; i < 10; ++i)
	{
		printf("%d\n", table[i]);
	}

	reverse(table, 10); 

	printf("\nReversed:\n");
	for (int i = 0; i < 10; ++i)
	{
		printf("%d\n", table[i]);
	}

	return 0;
}

void reverse(int *A, int n) {
	int i = 0, temp;

	while (i <= n/2 - 1) {
		temp = A[i];
		A[i] = A[n-i-1];
		A[n-i-1] = temp;
		++i;
	}
}
