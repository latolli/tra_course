#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASH_TABLE_SIZE 1048576
#define WORD_SIZE 50

typedef struct node {
    char* word;
    struct node* next;
} node;

node* hashtable[HASH_TABLE_SIZE];							// initialize hashtable that stores words
static int hashcounts[HASH_TABLE_SIZE];						// initialize hashtable, that keeps count of words

char str_top100[101][WORD_SIZE];							// top100 list for most popular words, stores words
int int_top100[101];										// top100 list for most popular words, stores word counts

unsigned long hash(unsigned char *str, int multiplier);
unsigned int insert_string(char *string);
void check100(int count, char *str);
void freehash(node* tmpnode);

int main() {
	char word[WORD_SIZE], tmpword[WORD_SIZE];				// variables for scannig words
	char filename[100];										// variable for textfile's name
	int hashresult;											// result of hashing
	char tmpstr[2];											// temporary variable for each letter in a word

	// initialize the hashtable with empty strings
    for(int i=0; i < HASH_TABLE_SIZE; i++){
        hashtable[i] = NULL;
    }
    // initialize the hashcounts with zeros
    for(int i=0; i < HASH_TABLE_SIZE; i++){
        hashtable[i] = 0;
    }
    // initialize top 100 list with zeros
	for (int i = 0; i < 101; ++i)
    {
    	int_top100[i] = 0;
    }


	// ask file's name from the user
	printf("Enter file's name in a form \"file.txt\": ");
	scanf("%s", filename);
	printf("Opening file: %s...\n", filename);

	// pointer for the file
	FILE *txtfile;	

	// check if the file exists in current directory
	if ((txtfile = fopen(filename, "r")) == NULL)
	{
		printf("Error with opening %s, program ends..", filename);
		return 0;
	}

	printf("Initializing hashtable...\n");

	// start clock for going through the textfile and inserting each word into hashtable
	clock_t begin = clock();

	// go through each word in file
	while (fscanf(txtfile, " %49[a-z'A-Z]", tmpword) == 1) {
		fscanf(txtfile, "%*[^a-zA-Z]", tmpword);

		// lower all the letters in tmpword
		for (int i = 0; i < strlen(tmpword); ++i)
		{
			tmpword[i] = tolower(tmpword[i]);
		}
		// if tmpword exists
		if (strlen(tmpword) > 0)
		{	
			// insert it to the hashtable
			hashresult = insert_string(tmpword);
			if(hashresult < 0){
	            printf("HASH TABLE FULL. CANCELING\n");
	            fclose(txtfile);
	            return 0;
	        }
		}
	}
	// close text file
	fclose(txtfile);

	// stop clock, calculate the time it took to store all words in hashtable and calculate top 100 words
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Hashtable succesfully initialized!\n");

    printf("\n100 most popular words are:\n");
    for (int i = 0; i < 100; ++i)
	{
		printf("%d: '%s' was found %u times\n",i+1, str_top100[i], int_top100[i]);
	}

	printf("\nTotal time: %.2fs\n", time_spent);

	// free the hashtable
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        if (hashtable[i] != NULL)
        {
            freehash(hashtable[i]);
        }
    }

	return 0;
}

// hash function, idea from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(unsigned char *str, int multiplier) {
    unsigned long hash = 5381;
    int num;

    while (num = *str++) {
        hash = ((hash << 5) + hash) + num;
    }
    // 1048575 is binary with only bits 1, so it basically makes sure that the key is in our hashtable range
    hash = (hash & (1048575))+multiplier;
    return hash;
}

// function for inserting a number to hashtable
unsigned int insert_string(char* string) {
    int n;
    // copy word to variable copystr
    char copystr[WORD_SIZE];
    strcpy(copystr, string);

    // get hash key for string
    n = hash(string, 0);
	node* new_node = (node*)malloc(sizeof(node));
	// if something went wrong, return -1
    if (new_node == NULL) {
    	return -1;
    }
    // else, store string to the hashtable
    else 
    {
        new_node->word = copystr;
        new_node->next = hashtable[n];
        hashtable[n] = new_node;
    }
    ++hashcounts[n];
    // check, if string belongs to current top 100 words
    check100(n, copystr);
    // return the index
    return n;
	
}


void check100(int n, char *str) {
	int count = 0, k;
	// if hashtable[n] isn't empty (it shouldnt be if this function was called)
    if (hashtable[n] != NULL)
    {	
    	count = hashcounts[n];
    }

    // go through top100 list
	for (k = 0; k < 101; ++k)
    {
    	// check if this num is more popular than the ones in current top 100
    	if (count > int_top100[k])
    	{
    		// if the word is already in top100 list
    		if (strcmp(str, str_top100[k]) == 0)
    		{	
    			// update that word's count and break the loop
    			int_top100[k] = count;
    			break;
    		}
    		// if it is more popular, move all numbers in top100 list one step to the right
    		for (int i = 101; i > k; --i)
    		{
    			int_top100[i] = int_top100[i - 1];
    		}
    		// place new string in it's correct place in top100
    		int_top100[k] = count;
    		// one step to the right in strtop also
    		for (int i = 101; i > k; --i)
    		{
    			sprintf(str_top100[i],"%s" ,str_top100[i - 1]);
    		}
    		// save the word in strtop100
    		sprintf(str_top100[k], "%s", str);
			break;    	
		}
    }
    // check if there is any copies of that word in top100 list
    for (int j = k+1; j < 101; ++j)
	{	
		// if there is, move every word after that one step to the left, so the copy will be overwritten
		if (strcmp(str, str_top100[j]) == 0)
		{
			for (int i = j; i < 101; ++i)
    		{
    			int_top100[i] = int_top100[i + 1];
    			sprintf(str_top100[i],"%s" ,str_top100[i + 1]);
    		}
		}
	}

}

// function to free the hashtable
void freehash(node* tmpnode) {
    if (tmpnode->next == NULL)
    {
        free(tmpnode);
    }

    else 
    {
        freehash(tmpnode->next);
        free(tmpnode);
    }
}
