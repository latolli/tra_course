#include <stdio.h>
#include <stdlib.h>

// For library quicksort
int compare(const void *a,const void *b){
 	int x = *(int *)(a);
 	int y = *(int *)(b);
 	return x-y;
}


int mode(int *A, int size);

int main() {
	int A[20] = {-1,-2,69,69,0,0,33,44,0,678,69,0,69,23,56,67,17,18,19,-1}, n=sizeof(A)/4, num_mode;
	qsort(A,n,sizeof(int),compare);

	num_mode = mode(A, n);

	printf("Mode of A is %d", num_mode);
	return 0;
}

int mode(int *A, int size) {
	int tmp_num, num_mode, count_mode = 1, counter = 1;
	tmp_num = A[0];
	num_mode = A[0];

	for (int i = 1; i < size; ++i)
	{
		if (tmp_num == A[i])
		{
			++counter;
			if (counter > count_mode)
			{
				count_mode = counter;
				num_mode = tmp_num;
			}
		}
		else {
			counter = 0;
			tmp_num = A[i];
		}
	}

	return num_mode;
}
