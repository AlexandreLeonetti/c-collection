#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>

// Function to trim whitespace from a string
void trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';
}

// Function to load environment variables from a file
void load_env_file(const char *filename, char *apiKey, char *apiSecret) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open .env file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *newline = strchr(line, '\n');
        if (newline) *newline = '\0';  // Remove newline character

        char *equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';  // Split key and value
            char *key = line;
            char *value = equals + 1;

            trim_whitespace(key);
            trim_whitespace(value);

            if (strcmp(key, "BINANCE_API_KEY") == 0) {
                strcpy(apiKey, value);
            } else if (strcmp(key, "BINANCE_SECRET") == 0) {
                strcpy(apiSecret, value);
            }
        }
    }

    fclose(file);
}

// Function to generate HMAC-SHA256 signature
void generate_signature(const char *apiSecret, const char *queryString, char *output) {
    unsigned char hmac_result[EVP_MAX_MD_SIZE];
    unsigned int len = EVP_MAX_MD_SIZE;

    HMAC_CTX *hmac = HMAC_CTX_new();
    HMAC_Init_ex(hmac, apiSecret, strlen(apiSecret), EVP_sha256(), NULL);
    HMAC_Update(hmac, (unsigned char *)queryString, strlen(queryString));
    HMAC_Final(hmac, hmac_result, &len);
    HMAC_CTX_free(hmac);

    for (int i = 0; i < len; i++) {
        sprintf(output + (i * 2), "%02x", hmac_result[i]);
    }
    output[len * 2] = '\0';
}

int main() {
    char apiKey[256] = {0};
    char apiSecret[256] = {0};
    char hardSecret[256] = "";
    //char apiSecret[256] = "secretKeyXYZ123"; // when assign the secret key as a string it works.
    // Load environment variables from .env file
    load_env_file("../.env", apiKey, apiSecret);// but loading from the env file apparently makes the wrong signature
    printf("%s\n",hardSecret);// = "";
    printf("%s\n",apiSecret); // in spite of generating the wrong signature, apiSecret is being printed correctly in the terminal
    char queryString[] = "abcd";  // Example query string
    char signature[65];

    generate_signature(apiSecret, queryString, signature);

    printf("Query string: %s\n", queryString);
    printf("Generated signature: %s\n", signature);
    printf("Full query string: %s&signature=%s\n", queryString, signature);

    return 0;
}
