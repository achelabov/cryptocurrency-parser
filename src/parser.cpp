#include <iostream>
#include <fstream>
#include <gumbo.h>

std::string readAll(const std::string &fileName)
{
    std::ifstream ifs;
    ifs.open(fileName);
    ifs.seekg(0, std::ios::end);
    size_t length = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::string buff(length, 0);
    ifs.read(&buff[0], length);
    ifs.close();

    return buff;
}

int main()
{
    std::cout << readAll("source.html") << std::endl;

    return 0;
}
