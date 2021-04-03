#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H
#include <string>

class HTTPDownloader 
{
public:
    HTTPDownloader();
    ~HTTPDownloader();

    std::string download(const std::string& url);
private:
    void* curl;
};
#endif  /* HTTPDOWNLOADER_H */
