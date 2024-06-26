#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to append a node at the end
void appendNode(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    struct Node* last = *headRef;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    while (last->next != NULL) {//going through the entire list until findind last element
        last = last->next;
    }
    
    last->next = newNode;
}

// Function to print the linked list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to free the linked list
void freeList(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    int someVar = 10;
    int* psomeVar = &someVar;
    int** ppSomeVar = &psomeVar;
    printf("%d \n", someVar);
    printf("%p \n", &someVar);
    printf("%d \n", *psomeVar);
    printf("content of psomeVar %p \n", psomeVar);
    printf("address of pSomevar : %p \n", &psomeVar);

    printf("Content of ppSomeVar %p \n", ppSomeVar);

    struct Node* head = NULL;
    printf("%p \n",head);
    printf("%p \n",&head);
    appendNode(&head, 1000);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);

    printList(head);

    freeList(head);
    return 0;
}
