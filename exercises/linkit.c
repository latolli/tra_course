#include <stdio.h>
#include <stdlib.h>

struct node {
	char person[150];
	struct node *next;
};

//Declaring list's head
struct node *head = NULL;


//Introduing all the functions
void menu();
void print_data();
void delete_data();
void ask_data(char *data);
void add_data(char *data);
int isEmpty();


int main() {
	int choice;
	char tmp_data[150];

	while(choice != 0){
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                //Store new piece of data to tmp_data
            	ask_data(tmp_data);
            	//Add data that is stored in tmp_data to linked list
            	add_data(tmp_data);
            	
                break;
            case 2:
                // Print current data and tell if there is no data at the moment
            	if (!isEmpty())
            	{
            		print_data();
            	}
            	else {
            		printf("The list is empty!\n");
            	}
                break;
            case 3:
            	//Delete current data, does nothing if the list is empty
            	delete_data();
            	printf("All data was successfully deleted.\n");
            	break;
            default: break;
        }
    }   
    return 0;
}

void menu() {
	//All the menu options
    printf("\nChoice:\n");
    printf("1 = Add personal data\n");
    printf("2 = Print all data\n");
    printf("3 = Delete all data\n");
    printf("0 = Exit\n");
}

void add_data(char *data) {
	//Create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));
	//Point it to old first node
	sprintf(link->person, "%s", data);
   	link->next = head;
    
   	//Point to the new first node
   	head = link;
}

void ask_data(char *data) {
	//Asks inputs from the user
	char firstname[50], lastname[50], address[50], addnum[50], phone[50];
	printf("\nEnter the person's name: ");
	scanf("%s", &firstname);
	scanf("%s", &lastname);
	printf("\nEnter the person's home address: ");
	scanf("%s", &address);
	scanf("%s", &addnum);
	printf("\nEnter the person's phone number: ");
	scanf("%s", &phone);

	//Store user's inputs into a string
	sprintf(data, "%s %s : %s %s : %s", firstname, lastname, address, addnum, phone);
}

void print_data() {
	//Print all person datas
	struct node *ptr = head;
	while(ptr != NULL) {
		printf("%s\n", ptr->person);
		ptr = ptr->next;
	}
}

int isEmpty() {
	//Check if the list is empty or not, returns 1 if empty
	struct node *ptr = head;
	if (ptr != NULL)
	{
		return 0;
	}
	return 1;
}

void delete_data() {
	//Delete all data
	struct node *ptr = head;
	while(ptr != NULL) {
		ptr = ptr->next;
		head = ptr;
	}
}
