#include "HTTPDownloader.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    std::string data((const char*) ptr, (size_t) size * nmemb);
    *((std::stringstream*)stream) << data << std::endl;

    return size * nmemb;
}

HTTPDownloader::HTTPDownloader() 
{
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader() 
{
    curl_easy_cleanup(curl);
}

std::string HTTPDownloader::download(const std::string& url) 
{
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) 
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    
    return out.str();
}
