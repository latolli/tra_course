#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASH_TABLE_SIZE 2000000
#define WORD_SIZE 100

typedef struct node {
    char* word;
    int counter;
} node;

unsigned long hash(unsigned char *str, int multiplier);
unsigned int insert_string(char *string, struct node* table);
unsigned int check_toplist(char *string, int count, struct node* table);

int main() {
    char tmpword[WORD_SIZE];                                // variable for scannig words
    char filename[2000];                                    // variable for textfile's name
    int hashresult;                                         // result of hashing

    node * hashtable = malloc(sizeof(node) * HASH_TABLE_SIZE);  // initialize hashtable that stores words
    node * top100list = malloc(sizeof(node) * 100);             // initialize list for top 100 words

    // initialize the hashtable with empty strings
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashtable[i].word = NULL;
    }
    // initialize the hashtable counts with zeros
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashtable[i].counter = 0;
    }
    // initialize the top 100 list with empty strings
    for(int i = 0; i < 100; i++)
    {
        top100list[i].word = NULL;
    }
    // initialize the top 100 list counts with zeros
    for(int i = 0; i < 100; i++)
    {
        top100list[i].counter = 0;
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
    while (fscanf(txtfile, " %99[A-Za-z']", tmpword) == 1) {
        fscanf(txtfile, "%*[^A-Za-z']", tmpword);

        // lower all the letters in tmpword
        for (int i = 0; i < strlen(tmpword); ++i)
        {
            tmpword[i] = tolower(tmpword[i]);
        }
        // insert it to the hashtable
        hashresult = insert_string(tmpword, hashtable);
        if(hashresult < 0){
            printf("ERROR WITH INSERTING TO HASHTABLE. CANCELING\n");
            fclose(txtfile);
            return 0;
        }
    }
    // close text file
    fclose(txtfile);

    // stop clock, calculate the time it took to store all words in hashtable and calculate top 100 words
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nHashtable initialized in: %.2fs\n", time_spent);

    printf("Hashtable succesfully initialized!\n");

    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        if (hashtable[i].word != NULL)
        {
            check_toplist(hashtable[i].word, hashtable[i].counter, top100list);
        }
    }

    // print 100 most popular words
    printf("\n100 most popular words are:\n");
    for (int i = 0; i < 100; ++i)
    {
        printf("%d. %d x %s\n", i+1, top100list[i].counter, top100list[i].word);
    }

    // free the hashtable
    printf("\nDeleting hashtable... ");
    free(hashtable);
    free(top100list);
    printf("Done!\n");

    // check total time
    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin) / CLOCKS_PER_SEC;
    printf("\nTotal time: %.2fs\n", time_spent2);

    return 0;
}

// hash function, idea from https://stackoverflow.com/questions/7666509/hash-function-for-string
unsigned long hash(unsigned char *str, int multiplier) {
    unsigned long hash = 5381;
    int num;

    while (num = *str++) {
        hash = ((hash << 5) + hash) + num;
    }
    // lets make sure tha thashkey stays in our hashtable range
    hash = hash % HASH_TABLE_SIZE + multiplier;
    return hash;
}

// function for inserting a number to hashtable
unsigned int insert_string(char* string, struct node* table) {
    int n;
    int len = strlen(string);

    // get hash key for string
    n = hash(string, 0);

    while(1) {
        // if index is empty
        if(table[n].word == NULL)
        {
            table[n].word = malloc(len+1);
            strcpy(table[n].word, string);
            ++table[n].counter;
            return n;
        }
        // if index contains the same word
        else if(strcmp(string, table[n].word) == 0)
        {
            ++table[n].counter;
            return n;
        }
        // if index conatins a different word, lets check the next index
        else if(strcmp(string, table[n].word) != 0)
        {
            n = (n+1) % HASH_TABLE_SIZE;
        }
        // if something that shouldn't happen happens, return -1
        else
        {
            printf("Something went wrong");
            return -1;
        }
    }

    return n;
    
}

// function for checking, if a word belongs to the current top 100 list
unsigned int check_toplist(char *string, int count, struct node* table) {
    int len = strlen(string);
    char tmpstr[WORD_SIZE];
    // go through top 100 list
    for (int i = 0; i < 100; ++i)
    {
        // if word's counter is bigger than some count in current top 100 list
        if (count > table[i].counter)
        {
            // move all smaller indexes one step to the right, starting from the last index
            for (int j = 99; j > i; --j)
            {
                // if a word is found
                if (table[j-1].word != NULL)
                {
                    len = strlen(table[j-1].word);
                    table[j].word = malloc(len+1);
                    strcpy(table[j].word, table[j-1].word);
                    table[j].counter = table[j-1].counter;
                }
            }
            // if that index is still empty
            if (table[i].word == NULL)
            {
                // insert new word to the index
                table[i].word = malloc(len+1);
                strcpy(table[i].word, string);
                table[i].counter = count;
                // no need to check further, because if this index was empty, all the following ones are also empty.
                return i;
            }
            else 
            {
                // if it contains old word, no need to malloc again, just replace the old word with this new one
                strcpy(table[i].word, string);
                table[i].counter = count;
                // no need to check further, we already found the right place for our new word
                return i; 
            }
        }
    }
}
