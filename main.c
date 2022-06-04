#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

size_t processData(char *data, size_t size, size_t nitems, void *userdata);

char *programweb = "https://pastebin.com/raw/F3m296eT";

int main()
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "curl_easy_init() failed\n");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, programweb);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, processData);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return 1;
    }
    curl_easy_cleanup(curl);

    return 0;
}

size_t processData(char *data, size_t size, size_t nitems, void *userdata)
{
    size_t bytes = size * nitems;
    int line = 1;
    for (int i = 0; i < bytes; i++)
    {
        printf("%c", data[i]);
        if (data[i] == '\n')
        {
            line++;
        }
    }
    return bytes;
}
