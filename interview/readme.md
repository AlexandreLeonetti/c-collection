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
printchar displays exactly one ASCII character from "A" to "Z" (inclusive) 
on multiple rows and columns using a graphical representation known as "ASCII Art".

We would like to do the reverse operation: finding a character from its graphical representation.
Implement the function scanChar (string str) so that it returns the character
associated with the given graphical representation (i.e. str = printChar (c) ).


If str does not match the graphical representation of any character from "A" to "Z", then
scanChar must return the character ?.

Lowercase letters do not have to be processed.

Example
The instruction printChar ('A'), returns this string (which contains newlines):

 #
# #
###
# #
# #

The instruction printChar ('B') returns another string, which looks like a "B" in ASCIl art, and so on.

The function scanChar is supposed to do the reverse operation:

string asciiArtA = "\

\n
##n

\nN
# \n\
# \n";
char scaResult = Answer:: scanChar(asciiArtA) =
cout «< scanResult << endl; // This line should output 'A'.
Hint: you can call the function printChar inside your function scanchar, as many times as you want.



answer :
```c++
#include <iostream>
#include <string>
#include <unordered_map>

std::string printChar(char c) {
    // This function generates the ASCII art for the character c.
    // For simplicity, we assume the function works correctly.
    // Here are a couple of example characters.
    
    std::unordered_map<char, std::string> charToArt = {
        {'A', "#\n#\n##\n# #\n# #\n# #\n"},
        {'B', "##\n# #\n##\n# #\n# #\n##\n"},
        // Add the remaining characters from 'C' to 'Z'
    };

    return charToArt[c];
}

class Answer {
public:
    /**
     * @return the character associated with the given ASCII art representation
     */
    static char scanChar(const std::string& str) {
        // Compare the given string with the ASCII art of all characters from 'A' to 'Z'
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (str == printChar(c)) {
                return c;
            }
        }
        // If no match is found, return character '2'
        return '2';
    }
};

int main() {
    std::string asciiArtA = "#\n#\n##\n# #\n# #\n# #\n";
    char scanResult = Answer::scanChar(asciiArtA);
    std::cout << scanResult << std::endl;  // This line should output 'A'.
    
    return 0;
}
```

answer in c :

```c
#include <stdio.h>
#include <string.h>

#define MAX_CHAR 128

typedef struct {
    char character;
    char *art;
} CharArt;

const CharArt charToArt[] = {
    {'A', "#\n#\n##\n# #\n# #\n# #\n"},
    {'B', "##\n# #\n##\n# #\n# #\n##\n"},
    // Add the remaining characters from 'C' to 'Z'
};

#define CHAR_ART_SIZE (sizeof(charToArt) / sizeof(CharArt))

char* printChar(char c) {
    for (int i = 0; i < CHAR_ART_SIZE; ++i) {
        if (charToArt[i].character == c) {
            return charToArt[i].art;
        }
    }
    return NULL;
}

char scanChar(const char* str) {
    for (int i = 0; i < CHAR_ART_SIZE; ++i) {
        if (strcmp(charToArt[i].art, str) == 0) {
            return charToArt[i].character;
        }
    }
    return '2';
}

int main() {
    char asciiArtA[] = "#\n#\n##\n# #\n# #\n# #\n";
    char scanResult = scanChar(asciiArtA);
    printf("%c\n", scanResult);  // This line should output 'A'.

    return 0;
}

```

>question 33/35
Instructions : The "next" function should return the smallest integer which is superior to n and
whose digits are all different from all of n's digits.

For example next (654321)
should return 700000.
If no such integer exists then the function must return -1.
Write the body of the next (n) function.
Note: n is a strictly positive integer lower than 2^31.

```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Determines if a given number contains any of the digits stored in the 'digits_used' array
bool contains_any_used_digits(int num, bool digits_used[10]) {
    while (num > 0) {
        if (digits_used[num % 10]) {
            return true;
        }
        num /= 10;
    }
    return false;
}

// Extracts all digits from 'n' and marks them in the 'digits_used' array
void mark_used_digits(int n, bool digits_used[10]) {
    memset(digits_used, false, 10 * sizeof(bool));
    while (n > 0) {
        digits_used[n % 10] = true;
        n /= 10;
    }
}

// Finds the smallest integer greater than 'n' with no digits in common with 'n'
int next(int n) {
    bool digits_used[10];
    mark_used_digits(n, digits_used);

    for (int test = n + 1; ; test++) {
        if (!contains_any_used_digits(test, digits_used)) {
            return test;
        }
        
        // If we are moving to a new magnitude (from 999 to 1000, etc.), we can jump over invalid ranges
        int digits = 0, tmp = test;
        while (tmp > 0) {
            digits++;
            tmp /= 10;
        }
        int pow10 = 1;
        for (int i = 0; i < digits - 1; i++) pow10 *= 10;

        // Find next clean decadic step that isn't affected by 'digits_used'
        if (test / pow10 % 10 == 9) {
            int nextStep = (test / pow10 + 1) * pow10;
            if (!contains_any_used_digits(nextStep, digits_used)) {
                test = nextStep - 1;  // decrement here because it will increment in the loop
            }
        }
    }
    return -1;  // Theoretically unreachable because INT_MAX is the highest it would go.
}

int main() {
    int numbers[] = {2, 901, 958, 3025, 654321, 1987, 123456789, 999999999};
    int num_tests = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < num_tests; i++) {
        int n = numbers[i];
        printf("Next number after %d is %d\n", n, next(n));
    }

    return 0;
}

```



>question 34/35
c++ only

>question 35/35
what is displayed by this code ?
```c
int main(){
    int a = 1;
    int *p = &a;
    *p++;

    printf("%d",a);
    return 0;

}

```

answer 1;






