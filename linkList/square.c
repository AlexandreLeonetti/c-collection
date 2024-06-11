//https://www.youtube.com/watch?v=sTFJtxJXkaY

#include <stdio.h>

int square(int v){
    v = v*v;
    return v;
}
int* psquare(int* v){
    *v = *v*(*v);
    return v;
};

int main (){
    int num = 6;
    printf("num = %d \n",num);
    psquare(&num);
    printf("num = %d \n",num);
    return 0;
}