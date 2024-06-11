#include <stdio.h>
#include <stdlib.h>


// struct Node
struct Node {
    int value;
    struct Node* next;
};

//declare head
struct Node* head;

// appendNode
/*
void appendNode( int value){
    if(head==NULL){
        struct Node* new = malloc(sizeof(struct Node));
        new->value = value;
        new->next = NULL;
        return;
    }

    struct Node* new = malloc(sizeof(struct Node));
    struct Node* current = head;

    while(current->next!=NULL){
         current= current->next;
    }
    current->next= new;

}
*/
// appendNode
void appendNode(int value) {
    struct Node* new = malloc(sizeof(struct Node));
    new->value = value;
    new->next = NULL;

    if (head == NULL) {
        head = new;
        return;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
}

// showLinks curent
void showLinks(){
    struct Node* current = head;
    while(current!=NULL){
        printf("value : %d \n",current->value);
        current = current->next;
    }
}

// main


int main (){
    appendNode(6);
    appendNode(7);
    appendNode(8);

    showLinks();
    // Free the allocated memory
    struct Node* current = head;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    return 0;
}

