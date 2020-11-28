#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start,end;
double totaltime;

unsigned int bigRandom() {
    unsigned int random =
    (((unsigned int) rand() << 0) & 0x00007FFF) |
    (((unsigned int) rand() << 15) & 0x3FFF8000);

    return random;
}

void randperm(int n, int *A);


int main() {
    int table[30], size = sizeof(table) / 4;
    srand(time(0));

    for (int i = 0; i < size; ++i)
    {
    	table[i] = i;
    }

    printf("Before A = ");
    for (int i = 0; i < size; ++i)
    {
    	printf("%d", table[i]);
    	if (i < size - 1)
    	{
    		printf(",");
    	}
    }
    printf("\n");

    // Start timer
    start = clock();
    randperm(size, table);

    //End timer
    end = clock();
    totaltime = (double)(end-start)/CLOCKS_PER_SEC;

    printf("After A = ");
    for (int i = 0; i < size; ++i)
    {
    	printf("%d", table[i]);
    	if (i < size - 1)
    	{
    		printf(",");
    	}
    }
    printf("\n");
    printf("Time: %f\n", start, end, totaltime);

    return 0;
}

void randperm(int n, int *A) {

    int tmp, i, x;
    for (i = 0; i  < n; ++i) {
        A[i] = i + 1;
    }
    for (i = 0; i  < n; ++i) {
        x = rand() % (i + 1);

        tmp = A[i];
        A[i] = A[x];
        A[x] = tmp;
    }
        
}
