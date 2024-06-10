#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    float *arr = NULL;

   // Print the address stored in the pointer 'arr'
    printf("Address stored in arr: %p\n", (void *)arr);
    // Allocate memory for an array of 5 integers
    arr = (float *)malloc(n * sizeof(float));

    // Check if memory has been successfully allocated
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Print the address stored in the pointer 'arr'
    printf("Address stored in arr: %p\n", (void *)arr);

    // Use the allocated memory
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2.11111111f;
    }

    // Print the allocated memory
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %f\n", i, arr[i]);
    }

    // Free the allocated memory
    free(arr);

    return 0;
}
