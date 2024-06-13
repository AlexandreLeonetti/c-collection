#include <stdio.h>
#include <stdlib.h>


// define struct Node
struct Node {
    int data;
    struct Node* next;
};

//create  a head and tail pointer
struct Node* head = NULL;
struct Node* tail = NULL;



// function to create Nodes
void createNode(int value){
    // malloc and append
    struct Node* new = malloc(sizeof(struct Node));
    new ->data = value;
    new ->next  = NULL;
        if (tail == NULL) {
        // If list is empty, initialize head and tail
        head = new;
        tail = new;
        return;
    }
    while(tail->next!=NULL){
        tail=tail->next;
    }
    tail->next = new;
    
    return;
}

// function to show linked list
void showList(){
    struct Node* current;
    current = head;
    while(current!= NULL){
        //printf("while show");
        printf("%d -> ",current->data);
        current = current->next;
    }
    printf("\n");
    return;
}

int main (){
    printf("log start");


    printf("Started program \n");
    // append other nodes;
    createNode(2);
    createNode(7);
    createNode(99);
    createNode(111);
    createNode(800);

    showList();


    return 0;
}