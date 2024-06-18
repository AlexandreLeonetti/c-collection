> question 1/35;
```c
int a  = 10;
```
> which statement returns the memory address of the variable a ?
answer : &a;

> question 2/35;

> question 2/35;
typedef struct {
    int a;
    int b;
} struct_type; // alias struct_type

struct_type s;

> to access the variable a of the structure s, the statement is...
answer s.a;

> question 3/35;
> what is printed by this code ?
```c
#include <stdio.h>


int main(){

    const char* p = "hello";
    p="world";

    printf("%s \n",p);
    return 0;
}

```

answer : "world"

>question 4/35;
>which of these keywords represent primitive types in C ?
answer see primitive types in docu.

>question 5/35;
Implement the function findLargest(numbers) so it returns largest number from the numbers array

numbers
contains only integers.
• numbers
always contains at least one element, and never contains more than
10 elements.
• The integers are ranged from
-2^31
to
+2^31
(they always fit in a 32-bit
signed integer).


answer :
```c
#include <stdio.h>

/*  @params  numbers  array of integer numbers
*   @return the largest value among the numbers given in parameters
*/
int findLargest(int numbers[], int size) {
    // Implement your logic here
    int largest = numbers[0];
    for (int i = 1; i < size; ++i) {
        if (numbers[i] > largest) {
            largest = numbers[i];
        }
    }
    return largest;
}

int main() {
    // Example usage
    int arr[] = {12, 5, 27, 8, 15};
    int size = sizeof(arr) / sizeof(arr[0]);

    int largest = findLargest(arr, size);
    printf("Largest number: %d\n", largest);

    return 0;
}
```

> question 6/35;
typedef struct x {
    int a ;
    int b ;
} myStruct;

to access the variable a from the ps pointer the statement is ?
answer :
```c
#include <stdio.h>
#include <stdlib.h> // For malloc and free

typedef struct {
    int a;
    int b;
} myStruct;

int main() {
    myStruct* ps = malloc(sizeof(myStruct));
    if (ps == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    ps->a = 10;
    ps->b = 20;

    printf("Value of a: %d\n", ps->a);  // Output: Value of a: 10

    free(ps);  // Remember to free dynamically allocated memory

    return 0;
}
```
> question 7/35;
correct pointer declaration for an integer?
answer :
int* p;


> question 8/35;
what is printed by this code :
int a = 5;
int* p = &a;

printf("%p", (void*)p);

answer : print memory address 0x7ffebcdcf79c

>question 9/35;

what is printed by this code ?
```c
typedef struct {
    char a;
    int b;
} myStruct;

int main() {
    myStruct s1;
    s1.a = 'a';
    s1.b = 3;

    myStruct s2 ;
    s2=s1;

    printf("%d \n",s2.b);
    return 0;
}

```
answer : 3

>question 10/35;
you declared the variable p using the following code :
MyClass* p = new MyClass(); c plus plus
equiv in c:
// Dynamic allocation in C
struct MyClass* p = malloc(sizeof(struct MyClass));

after using this variable you no longer need it.
which statement do you write ?


equivalent in C :
answer :
```c
#include <stdio.h>
#include <stdlib.h> // Required for malloc and free

struct MyClass {
    int data;
    // You can add more fields as needed
};

struct MyClass* createMyClass() {
    struct MyClass* p = malloc(sizeof(struct MyClass));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    // Initialize fields as needed
    p->data = 0; // Example initialization

    return p;
}

void destroyMyClass(struct MyClass* p) {
    free(p);
}

int main() {
    struct MyClass* p = createMyClass();
    if (p == NULL) {
        return 1; // Exit program if memory allocation failed
    }

    // Use p as needed...

    destroyMyClass(p); // Free allocated memory when no longer needed

    return 0;
}
```


>question 11/35;

Write the body of the calc(array, n1, n2) function.
array is a vector of integers. The n1
and n2
parameters are integers defined by the
relation o
n1 <= n2 < array.size
The calc method should return the sum of the integers of array whose index belongs to the [n1; n2] interval.



answer :
```c
#include <stdio.h>

// Function to calculate the sum of elements in array from index n1 to n2
int calc(int array[], int n1, int n2) {
    int sum = 0;
    
    // Loop through the array from index n1 to n2
    for (int i = n1; i <= n2; ++i) {
        sum += array[i];
    }
    
    return sum;
}

int main() {
    // Example usage:
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n1 = 0, n2 = 4; // Example indices
    
    int result = calc(array, n1, n2);
    
    printf("Sum of elements from index %d to %d is: %d\n", n1, n2, result);
    
    return 0;
}

```


>question 12/35;

what is this printing ?
    char* s;
    printf("%s",s);

answer : (null)

>question 13/35;
youre implementing a library.
how do you manage unexpected behavior ?

answer :
```c

#include <stdio.h>

int main() {
    // Example of handling unexpected behavior
    int result = perform_operation();
    
    if (result < 0) {
        fprintf(stderr, "Error: Operation failed with code %d\n", result);
        // Optionally, you can exit the program or take corrective action
        return 1; // Return non-zero to indicate failure
    }
    
    // Continue with program execution
    return 0;
}
```

>question 14/35;
int i1 = 5;
int i2 = 2;
int i3 = i1/i2;
printf("%d",i3);
what is the ouput ?
answer 2

>question 15/35;
int i;
for(i=0; i<10; i++>){}
what is the value after the for loop ?
answer 10.

>question 16/35;
>question 17/35;
what is the ouput of this :
```c
#include <stdio.h>

typedef struct{
    int foo;

}Struct;

int main() {
    Struct struct1;
    struct1.foo=5;

    Struct struct2 = struct1;
    struct2.foo = 10;

    printf("%d \n",struct1.foo);


    
    return 0;
}
```
answer 5;

>question 18/35;
in STL from a performance point of view,
what is the most efficient container to access
an element using an index ?
answer only in c++

>question 19/35;
select values that are considered as true in the following statement:
```c
//i can be equal to -1, 1, 10, 0.1
if(i){
    //statement
}
```


answer : all values are considered true. EXCEPTED 0

>question 20/35;
only c++ "at 14:45

>question 21/35;
only c++;

> question 22/35
What is printed cout <<
```c
#include <stdio.h>
int a(){
    printf("a");
    return 0;
}

int b(){
    printf("b");
    return 0;
}


int main(){

    if(a() && b()){
        printf("main");
    }

return 0;

}
```

answer:
Execution of a(): The function a() is called first. It prints "a" and returns 0.
Short-circuit Evaluation: Since the logical AND (&&) operator is used, and the first operand (a()) evaluates to 0 (which is considered false in C), the second operand (b()) is never evaluated. This is known as "short-circuiting". The b() function does not get executed because the result of the AND operation is already determined to be false by the first operand.
Inside the If Statement: Because the result of a() && b() is false (due to a() returning 0), the block inside the if statement that would print "main" is not executed.

>question 23/35;
only c++;

>question 24/35;
//17:00
what is the ouput of the following code :
```c
#include <stdio.h>


int foo(){
    static int i=1;
    i++;
    return i;
}

int main(){

    int value;

    value = foo();
    value =foo();

    printf("%d \n",value);

return 0;

}
```

answer 3;

> question 25/35;
variables are case sensitive;
answer yes;


>question 26/35;
int m = 5%2;
what is the value of m ?
answer 1;

>question 27/35;
only c++

>question 28/35;
>question 29/35;
only c++

>question 30/35;
what is the index of an array of 19 elements;
answer 18;

>question 31/35;
what is the ouput:
```c
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
```
answer 0 2;

>question 32/35;//19:30

