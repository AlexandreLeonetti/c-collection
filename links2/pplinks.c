#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

void append(struct Node** headRef , int value){
    struct Node* new = malloc(sizeof(struct Node));
    new -> data = value;
    new -> next = NULL;

   // if head is empty, make new node as head.
   if(*headRef==NULL) {
    *headRef = new;
    return;
   }

   // mopve headRef to next one
   struct Node* tail = *headRef;
    while (tail->next !=NULL){
        tail= tail->next;
    }
    tail->next = new;
}

void show(struct Node* node){
   while(node!=NULL) {
    printf("%d -> ",node->data);
    node = node->next;
   }
   printf("\n");
}

int main (){
    struct Node* h = malloc(sizeof(struct Node));

    append(&h,1);
    append(&h,9);
    append(&h,33);
    append(&h,10000);
    show(h);//using &h would require show to have a Node** arg, and then dereference it to do the same thing
    return 0;
}