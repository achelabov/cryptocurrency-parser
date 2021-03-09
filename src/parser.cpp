#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <gumbo.h>

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

static void search_for_links(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT)
    {
        return;
    }

    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A && (a = gumbo_get_attribute(&node->v.element.attributes, "href")))
    {
        std::cout << href->value << std::endl;
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) 
    {
        search_for_links(static_cast<GumboNode*>(children->data[i]));
    }
}

int main()
{
    GumboOutput* output = gumbo_parse(get_html("source.html").c_str());
    search_for_links(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    return 0;
}
