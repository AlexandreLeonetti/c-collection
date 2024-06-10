#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Static allocation
    char staticStr1[10] = "hello";
    char staticStr2[] = "world";

    printf("Static strings: %s %s\n", staticStr1, staticStr2);

    // Dynamic allocation
    char *dynamicStr = (char*)malloc(100 * sizeof(char));
    if (dynamicStr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(dynamicStr, "dynamic allocation");

    printf("Dynamic string: %s\n", dynamicStr);

    // Free dynamically allocated memory
    free(dynamicStr);

    return 0;
}
