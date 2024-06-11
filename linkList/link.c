#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void link( int data){
    struct Node* new = malloc(sizeof(struct Node)); 
    new->data = data;
    new->next = NULL;

    if(head == NULL){
        head = new;
        tail = new;
    }else{
        tail->next = new;
        tail = new;
    }

    return;
}

void printLinks(){

    struct Node* track = head;
    while(track!=NULL){
        printf("%d \n",track->data);
        track = track->next;
    }
 return;
}


int main(){
    link(11);
    link(15);
    link(77);

    printLinks();
    return 0;
}
