
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
