#include "../src/HTTPDownloader.h"
#include <fstream>
#include <string>

int main()
{
    std::ofstream fout;
    HTTPDownloader downloader;
    std::string content = downloader.download("https://bitinfocharts.com/ru/markets/");
    
    fout.open("../html/source.html");
    fout << content;
    fout.close();
}
