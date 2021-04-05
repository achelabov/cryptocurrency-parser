#include <iostream>
#include <string>
#include <fstream>
#include <gumbo.h>
#include "Volatility.h"

std::string get_html(const std::string &fileName)
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

double GetVolatility(const std::string wszPair, int vtype) 
{
    if (vtype != 2 || vtype != 4) return -1;

//  std::wstring w{ wszPair };
//  std::string s(w.begin(), w.end());

    std::string source = get_html("../html/source.html");
    Volatility cv;

    return cv.FindData(source, wszPair, (VOLTYPE)vtype);
}

int main()
{
    std::string pair = "1";
    int price = 2;
    double result = GetVolatility(pair, price);
    std::cout << result << std::endl;

    return 0;
}
