#include <stdio.h>
#include <stdlib.h>

//define the node structure
struct Node {
    int data;
    struct Node* next;
};

//function to create a node
struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(!newNode){
        printf("memory allocation failed");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
};



//function append node
void appendNode(struct Node** headRef, int data){
    struct Node* newNode = createNode(data);
    struct Node* last = *headRef;

    if(*headRef == NULL){
        *headRef = newNode;
        return;
    }

    while(last->next != NULL){ //going through all list
        last=last->next;
    }

    last->next = newNode;
}

//function to print a list

void printList(struct Node* n){
    while(n!=NULL){
        printf("%d \n",n->data);
        n=n->next;
    }
    printf("NULL\n");
}


//function to free the linked list
// Function to free the linked list
void freeList(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


int main(){
    struct Node* head = NULL;

    appendNode(&head,1);
    appendNode(&head, 5);
    appendNode(&head,99);
    appendNode(&head,1000);
    printList(head);
    freeList(head);


    return 0;
};