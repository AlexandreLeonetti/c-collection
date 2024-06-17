/*
Instructions : 
The next function should return the smallest integer which is superior
to whose digits are all different from all of n's digits.
For example next (654321)
should return 700000.
If no such integer exists then the function must return -1.
Write the body of the next (n) function.
Note: n is a strictly positive integer lower than 2^31.
and
in c :
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool hasCommonDigits(int num, bool digits[]) {
    while (num > 0) {
        int digit = num % 10;
        if (digits[digit]) {
            return true;
        }
        num /= 10;
    }
    return false;
}

int next(int n) {
    // Create an array to store which digits are present in n
    bool digits[10] = {false};
    int temp = n;

    // Mark the digits present in n
    while (temp > 0) {
        int digit = temp % 10;
        digits[digit] = true;
        temp /= 10;
    }

    // Start looking for the next number with unique digits
    for (int i = n + 1; i < 2147483647; ++i) {
        if (!hasCommonDigits(i, digits)) {
            return i;
        }
    }

    // If no such number is found, return -1
    return -1;
}

int main() {
    // Testing different inputs as specified
    printf("%d\n", next(2));       // Should print 3
    printf("%d\n", next(901));     // Should print 2222
    printf("%d\n", next(958));     // Should print 1000
    printf("%d\n", next(3025));    // Should print 4111
    printf("%d\n", next(654321));  // Should print 700000

    return 0;
}
