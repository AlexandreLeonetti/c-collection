#include <stdio.h>

int main(){
    int a = 1;
    int *p = &a;

    *p++;
    *p++;
    printf("%d",a);
    return 0;

}
