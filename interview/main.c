#include <stdio.h>


int main(){
int s = 0;
    switch(s){
        case 1 : printf("1");
        case 0 : printf("0\n");
        case 2 : printf("2\n");
    }

/* fall through behavior 0, 2*/

return 0;

}
