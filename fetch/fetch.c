#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Callback function to handle the data received from the server
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    size_t total_size = size * nmemb;
    strncat(data, ptr, total_size);
    return total_size;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    char data[1024] = {0}; // Buffer to store the response data

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://ip.jsontest.com");
        
        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse the JSON response
            cJSON *json = cJSON_Parse(data);
            if (json == NULL) {
                fprintf(stderr, "JSON parse error\n");
            } else {
                // Print the JSON response
                char *formatted_json = cJSON_Print(json);
                if (formatted_json) {
                    printf("%s\n", formatted_json);
                    free(formatted_json);
                }
                cJSON_Delete(json);
            }
        }

        // Clean up
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}
