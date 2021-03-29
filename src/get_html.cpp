#include <string>
#include <curl/curl.h>
#include <fstream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::ofstream fout;  

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "coinmarketcap.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        fout.open("../html/source.html");
        fout << readBuffer;
        fout.close();
    }
    return 0;
}
