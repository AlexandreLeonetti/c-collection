#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <openssl/hmac.h>
#include <time.h>
#include <cjson/cJSON.h>

#define API_KEY_ENV "BINANCE_API_KEY"
#define API_SECRET_ENV "BINANCE_SECRET"
#define MAX_LINE_LENGTH 256



// Structure to hold response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function to write response data into a struct
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// HMAC-SHA256 calculation
void hmac_sha256(const char *key, const char *data, unsigned char *result, unsigned int *len) {
    HMAC_CTX *hmac = HMAC_CTX_new();
    HMAC_Init_ex(hmac, key, strlen(key), EVP_sha256(), NULL);
    HMAC_Update(hmac, (unsigned char*)data, strlen(data));
    HMAC_Final(hmac, result, len);
    HMAC_CTX_free(hmac);
}

// Generate query string with HMAC signature
void generateQueryString(char *queryString, const char *symbol, double quantity, const char *apiSecret) {
    long timestamp = time(NULL) * 1000;
    printf("Timestamp: %ld\n", timestamp); // Debug

    sprintf(queryString, "symbol=%s",
            symbol );

    printf("Query string before signature: %s\n", queryString); // Debug

    unsigned char hmac_result[EVP_MAX_MD_SIZE];
    unsigned int len = EVP_MAX_MD_SIZE;
    hmac_sha256(apiSecret, queryString, hmac_result, &len);

    char signature[65];
    for(int i = 0; i < len; i++) {
        sprintf(signature + (i * 2), "%02x", hmac_result[i]);
    }
    signature[64] = '\0'; // Null-terminate the signature

    printf("Generated signature: %s\n", signature); // Debug

    strcat(queryString, "&signature=");
    strcat(queryString, signature);

    printf("Query string after signature: %s\n", queryString); // Debug
}

// Function to perform isolated buy
void isolatedBuyBor(const char *symbol, double quantity, const char *apiKey, const char *apiSecret) {
    printf("im in buy");
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {

        char queryString[1024];
        generateQueryString(queryString, symbol, quantity, apiSecret);
        /**/
        printf("queryString 1024 : \n");
        printf("%s\n",queryString);
        char url[1024] = "https://api.binance.com/sapi/v1/margin/order?";
        strcat(url, queryString);
        printf("url \n");
        printf("%s",url);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        char apiHeader[128];
        sprintf(apiHeader, "X-MBX-APIKEY: %s", apiKey);
        headers = curl_slist_append(headers, apiHeader);
        /*
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
*/

        if (curl_easy_setopt(curl, CURLOPT_URL, url) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt URL failed\n");
            return;
        }
        if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt WRITEFUNCTION failed\n");
            return;
        }
        if (curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt WRITEDATA failed\n");
            return;
        }
        if (curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt HTTPHEADER failed\n");
            return;
        }
        if (curl_easy_setopt(curl, CURLOPT_POSTFIELDS, queryString) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt POSTFIELDS failed\n");
            return;
        }
        if (curl_easy_setopt(curl, CURLOPT_POST, 1L) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt POST failed\n");
            return;
        }
        

        // Enable verbose mode
        if (curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L) != CURLE_OK) {
            fprintf(stderr, "curl_easy_setopt VERBOSE failed\n");
            return;
        }


        // Enable verbose mode
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", chunk.memory);
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        free(chunk.memory);
        
    }

    curl_global_cleanup();
}

// Trim whitespace from a string
void trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';
}


// Load environment variables from a file
void load_env_file(const char *filename, char *apiKey, char *apiSecret) {
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
            char *key = line;
            char *value = equals + 1;

            trim_whitespace(key);
            trim_whitespace(value);

            printf("Key: '%s', Value: '%s'\n", key, value); // Debug output

            if (strcmp(key, "BINANCE_API_KEY") == 0) {
                strcpy(apiKey, value);
                //printf("API Key loaded: %s\n", apiKey); // Debug output
            } else if (strcmp(key, "BINANCE_SECRET") == 0) {
                strcpy(apiSecret, value);
                //printf("API Secret loaded: %s\n", apiSecret); // Debug output
            }
        }
    }
    printf("returning");
    fclose(file);
    return;
}

int main() {
    char apiKey[256] = {0};
    char apiSecret[256] = {0};

    // Load environment variables from .env file
    load_env_file("../.env", apiKey, apiSecret);

    const char *symbol = "BTCUSDT";
    double quantity = 0.001;
    printf("testing final");
    // Debug statements to verify environment variables
    printf("Final API Key: %s \n", apiKey);
    printf("Final API Secret: %s \n new line\n", apiSecret);
    printf("about to check if\n");
    
    if (strlen(apiKey) == 0 || strlen(apiSecret) == 0) {
        fprintf(stderr, "API key and secret must be set in environment variables\n");
        return EXIT_FAILURE;
    }
    printf("before buy\n");
    isolatedBuyBor(symbol, quantity, apiKey, apiSecret);
    printf("after buy\n");

    return 0;
}

