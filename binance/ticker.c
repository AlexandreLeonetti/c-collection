#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

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
        // out of memory
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Function to get ticker price
double getTickerPrice(const char *symbol) {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  // will be grown as needed by the realloc in the WriteMemoryCallback
    chunk.size = 0;    // no data at this point

    char url[256];
    snprintf(url, sizeof(url), "https://api.binance.com/api/v3/ticker/price?symbol=%s", symbol);

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    res = curl_easy_perform(curl_handle);

    double price = 0.0;

    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        cJSON *json = cJSON_Parse(chunk.memory);
        if (json == NULL) {
            fprintf(stderr, "Error parsing JSON\n");
        } else {
            cJSON *priceItem = cJSON_GetObjectItemCaseSensitive(json, "price");
            if (cJSON_IsString(priceItem) && (priceItem->valuestring != NULL)) {
                price = atof(priceItem->valuestring);
            } else {
                fprintf(stderr, "Price data not found for symbol %s\n", symbol);
            }
            cJSON_Delete(json);
        }
    }

    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    curl_global_cleanup();

    return price;
}

int main() {
    const char *symbol = "BTCUSDT";
    double price = getTickerPrice(symbol);
    if (price > 0) {
        printf("The price of %s is: %.2f\n", symbol, price);
    } else {
        printf("Failed to get the price of %s\n", symbol);
    }

    return 0;
}
