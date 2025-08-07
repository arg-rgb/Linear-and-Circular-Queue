#include<stdio.h>
#include<stdlib.h>

void CqInsert();
void CqDelete();
void display();
int *queue,size,front = -1,rear = -1;

int main(){
    int n;
    printf("Enter the initial size of Queue : ");
    scanf("%d",&size);
    queue = (int *)malloc(size * sizeof(int));
    if(queue == NULL){
        printf("Memory Allocation Failed...Try again...\n");
        exit(0);
    }
    do{
        printf("Menu:\n1. insert\n2. delete\n3. display\n4. exit");
        printf("\nEnter your choice : ");
        scanf("%d",&n);
        switch(n){
            case 1: CqInsert(); break;
            case 2: CqDelete(); break;
            case 3: display(); break;
            case 4: free(queue);exit(0);
            default: printf("Enter a valid choice...!\n");
        }}while(1);
    free(queue);
    return 0;
}

void CqInsert(){
    int *temp, newSize, item; 
    char decision;

    // Correct condition to check if the circular queue is full
    if ((rear + 1) % size == front) {
        printf("Queue is full...\n");
        printf("Do you want to reallocate memory? (y/n): ");
        scanf(" %c", &decision);

        if (decision == 'y' || decision == 'Y') {
            printf("Enter new size: ");
            scanf("%d", &newSize);

            if (newSize <= size || newSize <= 0) {
                printf("Invalid size. Must be > %d\n", size);
                return;
            }

            temp = (int *)malloc(newSize * sizeof(int));
            if (temp == NULL) {
                printf("Memory Reallocation Failed... Please Try again later...!\n");
                return;
            }

            // Copy existing elements to new temp array (from front to rear)
            int i = front, j = 0;
            do {
                temp[j++] = queue[i];
                i = (i + 1) % size;
            } while (i != (rear + 1) % size);

            free(queue);
            queue = temp;
            front = 0;
            rear = j - 1;
            size = newSize;

            printf("Queue size increased to %d\n", size);
        } else {
            return;
        }
    }

    printf("Enter item to insert: ");
    scanf("%d", &item);

    // First insertion
    if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % size;
    }
    queue[rear] = item;
    printf("Successfully Inserted: %d\n", item);
}

void CqDelete() {
    if (front == -1) {
        printf("Queue is empty...\n");
        return;
    }
    
    int deletedItem = queue[front];
    
    // If only one element exists
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % size;
    }
    
    printf("Successfully deleted: %d\n", deletedItem);
}

void display() {
    if (front == -1) {
        printf("Queue is empty...Please insert an item...\n");
        return;
    }

    printf("Queue:\n");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % size;
    }

    printf("\nFront = %d, Rear = %d\n", front, rear);
}
