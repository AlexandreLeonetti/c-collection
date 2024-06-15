#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void load_env_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open .env file\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *newline = strchr(line, '\n');
        if (newline) *newline = '\0';  // Remove newline character

        char *equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';  // Split key and value
            const char *key = line;
            const char *value = equals + 1;
            setenv(key, value, 1);  // Set environment variable
        }
    }

    fclose(file);
}
