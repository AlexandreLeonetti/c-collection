#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void append(int value){
    struct Node* new = malloc(sizeof(struct Node)) ;
    new->data = value;
    new->next = NULL;

    if(head==NULL){
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

void show(){
    struct Node* cur = head;
    while(cur!=NULL){
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


int main(){
    printf("program starts \n");
    append(2);
    append(8);
    append(10);
    show();

    return 0;
}