#include <string>
#include <gumbo.h>

enum VOLTYPE
{
    price = 2,
    capitalization = 4
};

class Volatility
{
public:
    Volatility() {};
    double FindData(const std::string &szHtml, const std::string &pair, VOLTYPE vtype = price);
    ~Volatility() {};

protected:
    double FindTable(GumboNode* node);
    double FindTableRow(GumboNode* node);
    double GetVolatility(GumboNode* node);

private:
    std::string m_idtable = "t1";
    VOLTYPE m_column;
    std::string m_pair;
    static void *malloc_wrapper(void *unused, size_t size)
    {
        return malloc(size);
    }
    static void free_wrapper(void *unused, void *ptr)
    {
        free(ptr);
    }
};
