#include <stdio.h>

#define QUEUE_SIZE 10

void menu(){
    printf("Choice:\n");
    printf("1. Add customer\n");
    printf("2. Remove customer\n");
    printf("3. Exit\n\n");
}

int enqueue(int queue[QUEUE_SIZE], int pos);
int dequeue(int queue[QUEUE_SIZE], int pos);

int main(int argc, char **argv){
    int choice = 0;
    // Define needed variables
    int queue[QUEUE_SIZE];
    int customer = 0;

    while(choice != 3){
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                // Add a customer if possible
                customer = enqueue(queue, customer);
                break;
            case 2:
                // Remove a customer from queue if possible
                // and print customer's number
                customer = dequeue(queue, customer);
                break;
            default: break;
        }
    }
    return 0;
}

int enqueue(int queue[QUEUE_SIZE], int pos) {
    if (pos == QUEUE_SIZE)
    {
        printf("Queue is already full.\n");
        return pos;
    }
    else {
        queue[pos] = pos + 1;
        ++pos;
        printf("Customer number %d was added to the queue.", pos);
        return pos;
    }

}

int dequeue(int queue[QUEUE_SIZE], int pos) {
    if (pos == 0)
    {
        printf("You can't remove a customer froma an empty queue\n");
        return pos;
    }
    else {
        printf("Customer number %d was removed from the queue\n", pos);
        --pos;
        return pos;
    }
}