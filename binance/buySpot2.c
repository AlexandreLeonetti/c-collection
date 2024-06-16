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
void generateQueryString(char *queryString, const char *symbol, const char *quantity, const char *apiSecret) {
    long timestamp = time(NULL) * 1000;
    printf("Timestamp: %ld\n", timestamp); // Debug
    printf("queryString : %s",queryString);
    sprintf(queryString, "symbol=%s&side=BUY&type=LIMIT&timeInForce=GTC&quantity=%s&price=70000&recvWindow=50000&timestamp=%ld",  symbol, quantity, timestamp);

    //printf("Query string before signature: %s\n", queryString); // Debug

    unsigned char hmac_result[EVP_MAX_MD_SIZE];
    unsigned int len = EVP_MAX_MD_SIZE;
    hmac_sha256(apiSecret, queryString, hmac_result, &len);

    char signature[65];
    for(int i = 0; i < len; i++) {
        sprintf(signature + (i * 2), "%02x", hmac_result[i]);
    }
    signature[64] = '\0'; // Null-terminate the signature

   // printf("Generated signature: %s\n", signature); // Debug

    strcat(queryString, "&signature=");
    strcat(queryString, signature);

    printf("Query string after signature:\n %s\n\n", queryString); // Debug
}

// Function to perform isolated buy
void isolatedBuyBor(const char *symbol, const char  *quantity, const char *apiKey, const char *apiSecret) {
    CURL *curl;// Struct of type curl ?
    CURLcode res; // structure of type CURLcode ?
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {

        char queryString[1024];
        generateQueryString(queryString, symbol, quantity, apiSecret);
        /**/

        char url[1024] = "https://api.binance.com/api/v3/order?";
        //strcat(url, queryString);
        printf("url \n");
        printf("%s\n\n",url);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        char apiHeader[128];
        sprintf(apiHeader, "X-MBX-APIKEY: %s", apiKey);
        headers = curl_slist_append(headers, apiHeader);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); //write memory callback ??
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, queryString);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("\n reponse : \n\n %s\n", chunk.memory);
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
    end = str + strlen(str) - 1; //strlen
    while(end > str && isspace((unsigned char)*end)) end--;//isspace

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
    while (fgets(line, sizeof(line), file)) {//fgets ?
        char *newline = strchr(line, '\n');// strchr ?
        if (newline) *newline = '\0';  // Remove newline character

        char *equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';  // Split key and value
            char *key = line;
            char *value = equals + 1;

            trim_whitespace(key);
            trim_whitespace(value);


            if (strcmp(key, "BINANCE_API_KEY") == 0) { //strcmp ?
                strcpy(apiKey, value);// strcpy
            } else if (strcmp(key, "BINANCE_SECRET") == 0) {
                strcpy(apiSecret, value);
            }
        }
    }
    fclose(file);
    return;
}

int main() {
    char apiKey[256] = {0};
    char apiSecret[256] = {0};
    const char *symbol = "BTCUSDT";
    const char *quantity = "0.0007";


    // Load environment variables from .env file
    load_env_file("../.env", apiKey, apiSecret);
    
    if (strlen(apiKey) == 0 || strlen(apiSecret) == 0) {
        fprintf(stderr, "API key and secret must be set in environment variables\n");
        return EXIT_FAILURE;
    }

    isolatedBuyBor(symbol, quantity, apiKey, apiSecret);

    return 0;
}

