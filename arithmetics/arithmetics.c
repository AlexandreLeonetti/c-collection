//https://www.youtube.com/watch?v=BA4qkALiWEg
//12:38
#include <stdio.h>

#define BUFFER_SIZE 5

typedef struct {
    int  a[BUFFER_SIZE];
    int *pa;
} Circle ;

void  add(Circle *c, int data){
    *c->pa = data;
    if(c->pa !=  &c->a[BUFFER_SIZE - 1]){
        c->pa++;
    }else{
        c->pa = &c->a[0];
    }

    return;

}


int main(){
    Circle  circle1 = {0};
    circle1.pa = &circle1.a[0];

    //add(12);
    /*
    add(&circle1, 12);
    add(&circle1, 55);
    add(&circle1, 99);
    add(&circle1, 44);
    add(&circle1, 33);
    add(&circle1, 105);
    */


    for(int i=0; i<100; i++){
        add(&circle1, i);
    }


    for(int i=0; i<BUFFER_SIZE; i++){
        printf("%d ", circle1.a[i]);
    }

    printf("\n");
     return 0;

/*    int a[] = {12,44,19,62};
    int* pa = &a[0];

    pa++;

    printf("%d \n", *pa);
    */
}