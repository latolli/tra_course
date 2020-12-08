#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 49999

// Returns hash value
int hash(int number){
    return number%HASH_TABLE_SIZE;
}

// Insert a number to hash table
// Return -1 if table full
// Use linear probing
int insert_number(int number,int *table){
    int i = 0, j;
    j = hash(number);
    while (i < HASH_TABLE_SIZE) {
        j = (j+1)%HASH_TABLE_SIZE;
        if (table[j] == 0)
        {
            table[j] = number;
            return j;
        }
        ++i;
    }
    return -1;

}

// Search for a number in a hash table
// Assume that linear probing used
// Return the index in the table if found
// Return -1 if not found
int search_number(int number,int *table){
    int i = 0, j;
    j = hash(number);
    while (i < HASH_TABLE_SIZE && table[j] != 0) {
        if (table[j] == number)
        {
            return j;
        }
        ++i;
        if (i < HASH_TABLE_SIZE)
        {
            j = (j+1)%HASH_TABLE_SIZE;
        }

    }
    return -1;
}

int main(){
    // The hash table that we use
    int hashtable[HASH_TABLE_SIZE];
    char numbuf[10];
    FILE *numfile;

    // Initialize the table
    for(int i=0; i < HASH_TABLE_SIZE; i++){
        hashtable[i] = 0;
    }

    // Open the file containing the numbers
    numfile = fopen("task5_4_nums.txt","r");

    if (numfile == NULL){
		printf("ERROR READING THE FILE!\n");
		return 0;
	}

	// Read the numbers from the file
    while(fgets(numbuf,10,numfile)!=NULL){
        int number = atoi(numbuf);
        if(insert_number(number,hashtable) < 0){
            printf("HASH TABLE FULL. CANCELING\n");
            fclose(numfile);
            return 0;
        }
    }

    // Close the file
    fclose(numfile);

    // Searching for given numbers
    // 613695, 906429, 180551, 151841, 951585, 569127
    int searchtab[] = {613695, 906429, 180551, 151841, 951585, 569127};
    for(int i = 0; i < 6; i++){
        int rnum = searchtab[i];
        printf("Searching %u ... ",rnum);
        if(search_number(rnum,hashtable)<0){
            printf("... NOT found\n");
        }
        else {
            printf("%d ... WAS found\n",rnum);
        }
    }

    return 0;
}
