#include "../src/HTTPDownloader.h"
#include <iostream>
#include <string>

int main()
{
    HTTPDownloader downloader;
    std::string content = downloader.download("google.com");
    std::cout << content << std::endl;
    
    return 0;
}
