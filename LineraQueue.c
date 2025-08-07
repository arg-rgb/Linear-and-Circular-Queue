#include<stdio.h>
#include<stdlib.h>

void qInsert();
void qDelete();
void display();

int *queue,front=-1,rear=-1,size;

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
            case 1: qInsert(); break;
            case 2: qDelete(); break;
            case 3: display(); break;
            case 4: free(queue);exit(0);
            default: printf("Enter a valid choice...!\n");
        }}while(1);
    free(queue);
    return 0;
}

void qInsert(){
    int item,*temp,newSize;char decision;
    printf("Enter item to insert : \n");
    scanf("%d",&item);
    if(rear == size - 1){
        printf("Queue is Full...\n");
        printf("Do you want to reallocate memory ? (y/n) : ");
        scanf(" %c",&decision);
        if(decision == 'y' || decision == 'Y'){
            printf("Enter new size : ");
            scanf("%d",&newSize);
            if(newSize <= size){
                printf("New size should be greater than old size => %d\n",size);
                return;
            }
            temp = (int*)realloc(queue , newSize * sizeof(int));
            if(temp == NULL){
                printf("Memory Reallocation Failed...Please Try again later...!\n");
                return;
            }
            queue = temp;
            size = newSize;
            printf("Queue size increased to %d \n",size);
        }
        else{
            return;
        }
    }
    if(front == -1)
        front = 0;
    rear++;
    queue[rear] = item;
    printf("SuccessFully Inserted : %d\n",queue[rear]);
    return;
}

void qDelete(){
    if(front == -1 || front > rear){  
        printf("Queue is empty...Please insert an item...\n");
        return;
    }
    printf("SuccessFully Deleted : %d\n",queue[front]);
    front++;
}

void display(){
    int i;
    if(front == -1 || front>rear){
        printf("Queue is empty...\n");
        return;
    }
    printf("Queue :\n");
    for(i = front; i<=rear;i++){
        printf("| %3d ",queue[i]);
    }
    printf("\n");
    return;
}