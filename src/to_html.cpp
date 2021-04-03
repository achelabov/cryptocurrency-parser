#include "../src/HTTPDownloader.h"
#include <fstream>
#include <string>

int main()
{
    std::ofstream fout;
    HTTPDownloader downloader;
    std::string content = downloader.download("google.com");
    
    fout.open("../html/source.html");
    fout << content;
    fout.close();
}
